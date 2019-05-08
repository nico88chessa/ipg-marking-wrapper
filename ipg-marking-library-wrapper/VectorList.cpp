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
    /*msclr::auto_gcroot<ipgml::VectorList^> _vl;
    GCHandle handle;*/
    VECTORLIST_HANDLER handler;

public:
    VectorListPrivate(System::Collections::Generic::List<ipgml::Vector^>^ list) {
        //_vl = gcnew ipgml::VectorList(list);
        handler = GCHandle::ToIntPtr(GCHandle::Alloc(gcnew ipgml::VectorList(list))).ToPointer();
    }

    VectorListPrivate() {
        //_vl = gcnew ipgml::VectorList();
        handler = GCHandle::ToIntPtr(GCHandle::Alloc(gcnew ipgml::VectorList())).ToPointer();
    }

    VectorListPrivate(ipgml::PolygonProperties^ polygonProperties) {
        //_vl = gcnew ipgml::VectorList(polygonProperties);
        handler = GCHandle::ToIntPtr(GCHandle::Alloc(gcnew ipgml::VectorList(polygonProperties))).ToPointer();
    }

    VectorListPrivate(ipgml::BoxProperties^ boxProperties) {
        //_vl = gcnew ipgml::VectorList(polygonProperties);
        handler = GCHandle::ToIntPtr(GCHandle::Alloc(gcnew ipgml::VectorList(boxProperties))).ToPointer();
    }

    //VectorListPrivate(ipgml::VectorList^ other) {
    //    //_vl = other;
    //}

    ~VectorListPrivate() {
        //unlock();
        GCHandle h = GCHandle::FromIntPtr(IntPtr(handler));
        delete GCHandle::FromIntPtr(IntPtr(handler)).Target;
        handler = nullptr;
        h.Free();
    }

    ipgml::VectorList^ operator->() const {
        return static_cast<ipgml::VectorList^>(GCHandle::FromIntPtr(IntPtr(handler)).Target);
    }

    ipgml::VectorList^ get() const {
        return static_cast<ipgml::VectorList^>(GCHandle::FromIntPtr(IntPtr(handler)).Target);
    }

    //void* getManaged() {
    //    if (!handle.IsAllocated)
    //        handle = GCHandle::Alloc(_vl.get());
    //    IntPtr t(GCHandle::ToIntPtr(handle));
    //    void* obj = t.ToPointer();
    //    return obj;
    //}

    //void unlock() {
    //    if (handle.IsAllocated)
    //        handle.Free();
    //}
};


CONST_VECTORLIST_HANDLER VectorList::getManagedPtr() const {
    if (dPtr == nullptr)
        return nullptr;

    return dPtr->handler;
}

VectorList::VectorList() {
    dPtr = new VectorListPrivate();
}

VectorList::VectorList(std::list<Vector>& vectors) {
    
    auto list = gcnew System::Collections::Generic::List<ipgml::Vector^>();

    while (!vectors.empty()) {
        Vector v = vectors.front();
        vectors.pop_front();
        //GCHandle^ handle = GCHandle::FromIntPtr(IntPtr(c.getManagedPtr()));
        //ipgml::Vector^ vector = (ipgml::Vector^)handle->Target;
        ipgml::Vector^ vet = (ipgml::Vector^) GCHandle::FromIntPtr(IntPtr(const_cast<void*>(v.getManagedPtr()))).Target;
        list->Add(vet);
        //c.releaseManagedPtr();
    }

    dPtr = new VectorListPrivate(list);
}

//VectorList::VectorList(const VectorList & other) {
//    dPtr = new VectorListPrivate(other.dPtr->_vl->vectors);
//}

VectorList::VectorList(VectorList&& other) {
    this->dPtr = other.dPtr;
    other.dPtr = nullptr;
}

VectorList::VectorList(const PolygonProperties& polygonProperties) {

    CONST_POLYGONPROPERTIES_HANDLER pph = polygonProperties.getManagedPtr();
    GCHandle handle = GCHandle::FromIntPtr(IntPtr(const_cast<POINT_HANDLER>(pph)));
    ipgml::PolygonProperties^ ppManaged = (ipgml::PolygonProperties^) handle.Target;

    dPtr = new VectorListPrivate(ppManaged);

}

VectorList::VectorList(const BoxProperties& boxProperties) {

    CONST_BOXPROPERTIES_HANDLER pph = boxProperties.getManagedPtr();
    GCHandle handle = GCHandle::FromIntPtr(IntPtr(const_cast<POINT_HANDLER>(pph)));
    ipgml::BoxProperties^ bpManaged = (ipgml::BoxProperties^) handle.Target;

    dPtr = new VectorListPrivate(bpManaged);

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
        //dPtr->_vl->Append(vl.dPtr->_vl.get());
        (*dPtr)->Append(vl.dPtr->get());
    } catch (ipgml::LibraryException^ e) {

        System::String^ managedMessage = e->Message;
        msclr::interop::marshal_context context;
        std::string message = context.marshal_as<std::string>(managedMessage);
        throw LibraryException(message);

    }

}

int VectorList::count() const {
    return (*dPtr)->Count;
}

VectorWrapper VectorList::element(int i) const {

    try {

        ipgml::Vector^ v = (*dPtr)->Element(i); // qui la dll torna un reference
        GCHandle handle = GCHandle::Alloc(v);               // nessuna copia del vettore, punto allo stesso oggetto (reference)
        VectorWrapper res(GCHandle::ToIntPtr(handle).ToPointer());  // nessuna copia del vettore, punto allo stesso oggetto (reference)
        handle.Free();
        return res;

    } catch (ipgml::LibraryException^ e) {

        System::String^ managedMessage = e->Message;
        msclr::interop::marshal_context context;
        std::string message = context.marshal_as<std::string>(managedMessage);
        throw LibraryException(message);

    }

    return VectorWrapper();

}

void VectorList::shift(float x, float y, float z) {
    if (this->dPtr == nullptr)
        return;
    (*dPtr)->Shift(x, y, z);
}

void VectorList::rotate(double z) {
    if (this->dPtr == nullptr)
        return;
    (*dPtr)->Rotate(z);
}

void VectorList::rotate(double x, double y, double z) {
    if (this->dPtr == nullptr)
        return;
    (*dPtr)->Rotate(x, y, z);
}

void VectorList::rotate(float z) {
    if (this->dPtr == nullptr)
        return;
    (*dPtr)->Rotate(z);
}

void VectorList::rotate(float x, float y, float z) {
    if (this->dPtr == nullptr)
        return;
    (*dPtr)->Rotate(x, y, z);
}

void VectorList::reverseOrder() {
    if (this->dPtr == nullptr)
        return;
    (*dPtr)->ReverseOrder();
}

void VectorList::scale(float scaleFactor) {
    if (this->dPtr == nullptr)
        return;
    (*dPtr)->Scale(scaleFactor);
}

void VectorList::scale(float x, float y, float z) {
    if (this->dPtr == nullptr)
        return;
    (*dPtr)->Scale(x, y, z);
}

std::list<VectorWrapper> VectorList::vectors() {

    if (this->dPtr == nullptr)
        return std::list<VectorWrapper>();

    std::list<VectorWrapper> list;

    int size = this->count();
    for (int i = 0; i < size; ++i) {
        list.push_back(this->element(i));
    }
    return list;
}

void VectorList::addVector(const Vector& v) {

    CONST_POINT_HANDLER ph = v.getManagedPtr();
    GCHandle handle = GCHandle::FromIntPtr(IntPtr(const_cast<POINT_HANDLER>(ph)));
    ipgml::Vector^ vManaged = (ipgml::Vector^) handle.Target;
    (*dPtr)->vectors->Add(vManaged);

}

Point VectorList::center() const {
    
    if (this->dPtr == nullptr)
        return Point();

    ipgml::Point^ centerManaged = (*dPtr)->Center; // qui viene fatta una copia del Punto dalla dll ipg
    GCHandle handle = GCHandle::Alloc(centerManaged);  // nessuna copia del Punto, punto allo stesso oggetto (copia)  
    Point res(GCHandle::ToIntPtr(handle).ToPointer()); // nessuna copia del Punto, punto allo stesso oggetto (copia)
    handle.Free();
    return res;

}

//void* VectorList::getManagedPtr() {
//    if (dPtr == nullptr)
//        return nullptr;
//
//    void* obj = dPtr->getManaged();
//    return obj;
//}
//
//void VectorList::releaseManagedPtr() {
//    dPtr->unlock();
//}

std::ostream & ipg_marking_library_wrapper::operator<<(std::ostream & os, const VectorList & obj) {
    int size = obj.count();
    for (int i = 0; i < size; ++i)
        os << obj.element(i) << std::endl;
    return os;
}
