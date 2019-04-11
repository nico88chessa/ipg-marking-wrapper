#using "ipg/IpgMarkingGraphicsLibrary.dll"

#include "stdafx.h"
#include <msclr/auto_gcroot.h>
#include <msclr/marshal_cppstd.h>

#include "PointList.h"
#include "LibraryException.h"


using namespace System;
using namespace System::Runtime::InteropServices;
namespace ipgml = IpgMarkingGraphicsLibrary;

using namespace ipg_marking_library_wrapper;

class ipg_marking_library_wrapper::PointListPrivate {
public:
    msclr::auto_gcroot<ipgml::PointList^> _pl;
    GCHandle handle;

public:
    PointListPrivate(System::Collections::Generic::List<ipgml::Point^>^ list) {
        _pl = gcnew ipgml::PointList(list);
    }

    PointListPrivate() {
        _pl = gcnew ipgml::PointList();
    }

    PointListPrivate(ipgml::PolygonProperties^ polygonProperties) {
        _pl = gcnew ipgml::PointList(polygonProperties);
    }

    PointListPrivate(ipgml::PointList^ other) {
        _pl = other;
    }

    ~PointListPrivate() {
        unlock();
    }

    void* getManaged() {
        if (!handle.IsAllocated)
            handle = GCHandle::Alloc(_pl.get());
        IntPtr t(GCHandle::ToIntPtr(handle));
        void* obj = t.ToPointer();
        return obj;
    }

    void unlock() {
        if (handle.IsAllocated)
            handle.Free();
    }
};

PointList::PointList() {
    dPtr = new PointListPrivate();
}

PointList::PointList(std::list<Point>& points) {
    
    auto list = gcnew System::Collections::Generic::List<ipgml::Point^>();

    while (!points.empty()) {
        Point c = points.front();
        points.pop_front();
        GCHandle^ handle = GCHandle::FromIntPtr(IntPtr(c.getManagedPtr()));
        ipgml::Point^ point = (ipgml::Point^)handle->Target;
        list->Add(point);
        c.releaseManagedPtr();
    }

    dPtr = new PointListPrivate(list);
}

PointList::PointList(PointList && other) {
    this->dPtr = other.dPtr;
    other.dPtr = nullptr;
}

PointList::PointList(const PolygonProperties& polygonProperties) {

    ipgml::PolygonProperties^ managedPolygonProperties = gcnew ipgml::PolygonProperties(
        (int)polygonProperties.getNumberOfSides(),
        polygonProperties.getRadius());
    
    dPtr = new PointListPrivate(managedPolygonProperties);

}

PointList::~PointList() {
    if (dPtr != nullptr)
        delete dPtr;
}

void PointList::append(const PointList& pl) {
    if (dPtr == nullptr)
        return;

    // BUGFIX IPG 11/04/2019 - questo bypassa un problema sulle librerie dell'ipg (allocazione memoria infinita)
    if (pl.dPtr == this->dPtr)
        return;
    // FINE BUGFIX

    try {
        dPtr->_pl->Append(pl.dPtr->_pl.get());
    } catch (ipgml::LibraryException^ e) {

        System::String^ managedMessage = e->Message;
        msclr::interop::marshal_context context;
        std::string message = context.marshal_as<std::string>(managedMessage);
        throw LibraryException(message);

    }

}

int PointList::count() const {
    return this->dPtr->_pl->Count;
}

Point PointList::element(int i) {

    try {

        ipgml::Point^ p = dPtr->_pl->Element(i); // qui la dll torna un reference
        GCHandle handle = GCHandle::Alloc(p);               // nessuna copia del Punto, punto allo stesso oggetto (reference)
        Point res(GCHandle::ToIntPtr(handle).ToPointer());  // nessuna copia del Punto, punto allo stesso oggetto (reference)
        handle.Free();
        return res;
    
    } catch (ipgml::LibraryException^ e) {

        System::String^ managedMessage = e->Message;
        msclr::interop::marshal_context context;
        std::string message = context.marshal_as<std::string>(managedMessage);
        throw LibraryException(message);

    }

    return Point();

}

void PointList::shift(float x, float y, float z) {
    if (this->dPtr == nullptr)
        return;
    this->dPtr->_pl->Shift(x, y, z);
}

void PointList::rotate(double z) {
    if (this->dPtr == nullptr)
        return;
    this->dPtr->_pl->Rotate(z);
}

void PointList::rotate(double x, double y, double z) {
    if (this->dPtr == nullptr)
        return;
    this->dPtr->_pl->Rotate(x, y, z);
}

void PointList::rotate(float z) {
    if (this->dPtr == nullptr)
        return;
    dPtr->_pl->Rotate(z);
}

void PointList::rotate(float x, float y, float z) {
    if (this->dPtr == nullptr)
        return;
    this->dPtr->_pl->Rotate(x, y, z);
}

Point PointList::center() const {
    
    if (this->dPtr == nullptr)
        return Point();

    ipgml::Point^ centerManaged = this->dPtr->_pl->Center; // qui viene fatta una copia del Punto dalla dll ipg
    GCHandle handle = GCHandle::Alloc(centerManaged);  // nessuna copia del Punto, punto allo stesso oggetto (copia)  
    Point res(GCHandle::ToIntPtr(handle).ToPointer()); // nessuna copia del Punto, punto allo stesso oggetto (copia)
    handle.Free();
    return res;

}

void* PointList::getManagedPtr() {
    if (dPtr == nullptr)
        return nullptr;

    void* obj = dPtr->getManaged();
    return obj;
}

void PointList::releaseManagedPtr() {
    dPtr->unlock();
}
