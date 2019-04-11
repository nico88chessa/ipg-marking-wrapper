#using "ipg/IpgMarkingGraphicsLibrary.dll"

#include "stdafx.h"
#include <msclr/auto_gcroot.h>
#include <msclr/marshal_cppstd.h>

#include "VectorList.h"
#include "LibraryException.h"


using namespace System;
using namespace System::Runtime::InteropServices;
namespace ipgml = IpgMarkingGraphicsLibrary;

using namespace ipg_marking_library_wrapper;


class ipg_marking_library_wrapper::VectorListPrivate {
public:
    msclr::auto_gcroot<ipgml::VectorList^> _vl;
    GCHandle handle;

public:
    VectorListPrivate(System::Collections::Generic::List<ipgml::Vector^>^ list) {
        _vl = gcnew ipgml::VectorList(list);
    }

    VectorListPrivate() {
        _vl = gcnew ipgml::VectorList();
    }

    VectorListPrivate(ipgml::PolygonProperties^ polygonProperties) {
        _vl = gcnew ipgml::VectorList(polygonProperties);
    }

    VectorListPrivate(ipgml::VectorList^ other) {
        _vl = other;
    }

    ~VectorListPrivate() {
        unlock();
    }

    void* getManaged() {
        if (!handle.IsAllocated)
            handle = GCHandle::Alloc(_vl.get());
        IntPtr t(GCHandle::ToIntPtr(handle));
        void* obj = t.ToPointer();
        return obj;
    }

    void unlock() {
        if (handle.IsAllocated)
            handle.Free();
    }
};


VectorList::VectorList() {
    dPtr = new VectorListPrivate();
}

VectorList::VectorList(std::list<Vector>& vectors) {
    
    auto list = gcnew System::Collections::Generic::List<ipgml::Vector^>();

    while (!vectors.empty()) {
        Vector c = vectors.front();
        vectors.pop_front();
        GCHandle^ handle = GCHandle::FromIntPtr(IntPtr(c.getManagedPtr()));
        ipgml::Vector^ vector = (ipgml::Vector^)handle->Target;
        list->Add(vector);
        c.releaseManagedPtr();
    }

    dPtr = new VectorListPrivate(list);
}

VectorList::VectorList(VectorList&& other) {
    this->dPtr = other.dPtr;
    other.dPtr = nullptr;
}

VectorList::VectorList(const PolygonProperties& polygonProperties) {

    ipgml::PolygonProperties^ managedPolygonProperties = gcnew ipgml::PolygonProperties(
        (int)polygonProperties.getNumberOfSides(),
        polygonProperties.getRadius());
    
    dPtr = new VectorListPrivate(managedPolygonProperties);

}

VectorList::~VectorList() {
    if (dPtr != nullptr)
        delete dPtr;
}

void VectorList::append(const VectorList& vl) {
    if (dPtr == nullptr)
        return;

    // BUGFIX IPG 11/04/2019 - questo bypassa un problema sulle librerie dell'ipg (allocazione memoria infinita)
    if (vl.dPtr == this->dPtr)
        return;
    // FINE BUGFIX

    try {
        dPtr->_vl->Append(vl.dPtr->_vl.get());
    } catch (ipgml::LibraryException^ e) {

        System::String^ managedMessage = e->Message;
        msclr::interop::marshal_context context;
        std::string message = context.marshal_as<std::string>(managedMessage);
        throw LibraryException(message);

    }

}

int VectorList::count() const {
    return this->dPtr->_vl->Count;
}

Vector VectorList::element(int i) const {

    try {

        ipgml::Vector^ v = dPtr->_vl->Element(i); // qui la dll torna un reference
        GCHandle handle = GCHandle::Alloc(v);               // nessuna copia del vettore, punto allo stesso oggetto (reference)
        Vector res(GCHandle::ToIntPtr(handle).ToPointer());  // nessuna copia del vettore, punto allo stesso oggetto (reference)
        handle.Free();
        return res;

    } catch (ipgml::LibraryException^ e) {

        System::String^ managedMessage = e->Message;
        msclr::interop::marshal_context context;
        std::string message = context.marshal_as<std::string>(managedMessage);
        throw LibraryException(message);

    }

    return Vector();

}

void VectorList::shift(float x, float y, float z) {
    if (this->dPtr == nullptr)
        return;
    this->dPtr->_vl->Shift(x, y, z);
}

void VectorList::rotate(double z) {
    if (this->dPtr == nullptr)
        return;
    this->dPtr->_vl->Rotate(z);
}

void VectorList::rotate(double x, double y, double z) {
    if (this->dPtr == nullptr)
        return;
    this->dPtr->_vl->Rotate(x, y, z);
}

void VectorList::rotate(float z) {
    if (this->dPtr == nullptr)
        return;
    dPtr->_vl->Rotate(z);
}

void VectorList::rotate(float x, float y, float z) {
    if (this->dPtr == nullptr)
        return;
    this->dPtr->_vl->Rotate(x, y, z);
}

Point VectorList::center() const {
    
    if (this->dPtr == nullptr)
        return Point();

    ipgml::Point^ centerManaged = this->dPtr->_vl->Center; // qui viene fatta una copia del Punto dalla dll ipg
    GCHandle handle = GCHandle::Alloc(centerManaged);  // nessuna copia del Punto, punto allo stesso oggetto (copia)  
    Point res(GCHandle::ToIntPtr(handle).ToPointer()); // nessuna copia del Punto, punto allo stesso oggetto (copia)
    handle.Free();
    return res;

}

void* VectorList::getManagedPtr() {
    if (dPtr == nullptr)
        return nullptr;

    void* obj = dPtr->getManaged();
    return obj;
}

void VectorList::releaseManagedPtr() {
    dPtr->unlock();
}

std::ostream & ipg_marking_library_wrapper::operator<<(std::ostream & os, const VectorList & obj) {
    int size = obj.count();
    for (int i = 0; i < size; ++i)
        os << obj.element(i) << std::endl;
    return os;
}
