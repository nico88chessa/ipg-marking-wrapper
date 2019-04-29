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
    //msclr::auto_gcroot<ipgml::PointList^> _pl;
    //GCHandle handle;
    POINTLIST_HANDLER handler;

public:
    PointListPrivate(System::Collections::Generic::List<ipgml::Point^>^ list) {
        //_pl = gcnew ipgml::PointList(list);
        handler = GCHandle::ToIntPtr(GCHandle::Alloc(gcnew ipgml::PointList(list))).ToPointer();
    }

    PointListPrivate() {
        //_pl = gcnew ipgml::PointList();
        handler = GCHandle::ToIntPtr(GCHandle::Alloc(gcnew ipgml::PointList())).ToPointer();
    }

    PointListPrivate(ipgml::PolygonProperties^ polygonProperties) {
        //_pl = gcnew ipgml::PointList(polygonProperties);
        handler = GCHandle::ToIntPtr(GCHandle::Alloc(gcnew ipgml::PointList(polygonProperties))).ToPointer();
    }

    //PointListPrivate(ipgml::PointList^ other) {
        //_pl = other;
    //}

    ~PointListPrivate() {
        //unlock();
        GCHandle h = GCHandle::FromIntPtr(IntPtr(handler));
        delete GCHandle::FromIntPtr(IntPtr(handler)).Target;
        handler = nullptr;
        h.Free();
    }

    ipgml::PointList^ operator->() const {
        return static_cast<ipgml::PointList^>(GCHandle::FromIntPtr(IntPtr(handler)).Target);
    }

    ipgml::PointList^ get() const {
        return static_cast<ipgml::PointList^>(GCHandle::FromIntPtr(IntPtr(handler)).Target);
    }

    /*void* getManaged() {
        if (!handle.IsAllocated)
            handle = GCHandle::Alloc(_pl.get());
        IntPtr t(GCHandle::ToIntPtr(handle));
        void* obj = t.ToPointer();
        return obj;
    }

    void unlock() {
        if (handle.IsAllocated)
            handle.Free();
    }*/
};


CONST_POINTLIST_HANDLER PointList::getManagedPtr() const {
    if (dPtr == nullptr)
        return nullptr;

    return dPtr->handler;
}

PointList::PointList() {
    dPtr = new PointListPrivate();
}

PointList::PointList(std::list<Point>& points) {
    
    auto list = gcnew System::Collections::Generic::List<ipgml::Point^>();

    while (!points.empty()) {
        Point c = points.front();
        points.pop_front();
        ipgml::Point^ point = (ipgml::Point^) GCHandle::FromIntPtr(IntPtr(const_cast<void*>(c.getManagedPtr()))).Target;
        //ipgml::Point^ point = (ipgml::Point^)handle->Target;
        //ipgml::Point^ point = c.getWrapped().dPtr->
        list->Add(point);
        //c.releaseManagedPtr();
    }

    dPtr = new PointListPrivate(list);
}

//PointList::PointList(const PointList& other) {
//    //dPtr = new PointListPrivate(other.dPtr->_pl->points);
//    ipgml::PointList^ pl = (ipgml::PointList^) GCHandle::FromIntPtr(IntPtr(other.dPtr->handler)).Target;
//    dPtr = new PointListPrivate(pl->points);
//}

PointList::PointList(PointList&& other) {
    this->dPtr = other.dPtr;
    other.dPtr = nullptr;
}

PointList::PointList(const PolygonProperties& polygonProperties) {

    CONST_POLYGONPROPERTIES_HANDLER pph = polygonProperties.getManagedPtr();
    GCHandle handle = GCHandle::FromIntPtr(IntPtr(const_cast<POINT_HANDLER>(pph)));
    ipgml::PolygonProperties^ ppManaged = (ipgml::PolygonProperties^) handle.Target;

    dPtr = new PointListPrivate(ppManaged);

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
        //dPtr->_pl->Append(pl.dPtr->_pl.get());
        (*dPtr)->Append(pl.dPtr->get());
    } catch (ipgml::LibraryException^ e) {

        System::String^ managedMessage = e->Message;
        msclr::interop::marshal_context context;
        std::string message = context.marshal_as<std::string>(managedMessage);
        throw LibraryException(message);

    }

}

int PointList::count() const {
    return (*dPtr)->Count;
}

Point PointList::center() const {

    if (this->dPtr == nullptr)
        return Point();

    ipgml::Point^ centerManaged = (*dPtr)->Center; // qui viene fatta una copia del Punto dalla dll ipg
    GCHandle handle = GCHandle::Alloc(centerManaged);  // nessuna copia del Punto, punto allo stesso oggetto (copia)  
    Point res(GCHandle::ToIntPtr(handle).ToPointer()); // nessuna copia del Punto, punto allo stesso oggetto (copia)
    handle.Free();
    return res;

}

PointWrapper PointList::element(int i) const {

    try {

        //ipgml::Point^ p = dPtr->_pl->Element(i); // qui la dll torna un reference
        ipgml::Point^ p = (*dPtr)->Element(i);
        GCHandle handle = GCHandle::Alloc(p);               // nessuna copia del Punto, punto allo stesso oggetto (reference)
        //PointWrapper* res = new PointWrapper(GCHandle::ToIntPtr(handle).ToPointer());  // nessuna copia del Punto, punto allo stesso oggetto (reference)
        PointWrapper res(GCHandle::ToIntPtr(handle).ToPointer());  // nessuna copia del Punto, punto allo stesso oggetto (reference)
        handle.Free();
        return res;  // copy elided
    
    } catch (ipgml::LibraryException^ e) {

        System::String^ managedMessage = e->Message;
        msclr::interop::marshal_context context;
        std::string message = context.marshal_as<std::string>(managedMessage);
        throw LibraryException(message);

    }

    return PointWrapper();

}

void PointList::shift(float x, float y, float z) {
    if (this->dPtr == nullptr)
        return;
    (*dPtr)->Shift(x, y, z);
}

void PointList::rotate(double z) {
    if (this->dPtr == nullptr)
        return;
    (*dPtr)->Rotate(z);
}

void PointList::rotate(double x, double y, double z) {
    if (this->dPtr == nullptr)
        return;
    (*dPtr)->Rotate(x, y, z);
}

void PointList::rotate(float z) {
    if (this->dPtr == nullptr)
        return;
    (*dPtr)->Rotate(z);
}

void PointList::rotate(float x, float y, float z) {
    if (this->dPtr == nullptr)
        return;
    (*dPtr)->Rotate(x, y, z);
}

std::list<PointWrapper> PointList::points() {

    if (this->dPtr == nullptr)
        return std::list<PointWrapper>();

    std::list<PointWrapper> list;
    
    int size = this->count();
    for (int i = 0; i < size; ++i) {
        list.push_back(this->element(i));
    }
    return list;
}

void PointList::addPoint(const Point& p) {

    CONST_POINT_HANDLER ph = p.getManagedPtr();
    GCHandle handle = GCHandle::FromIntPtr(IntPtr(const_cast<POINT_HANDLER>(ph)));
    ipgml::Point^ pManaged = (ipgml::Point^) handle.Target;
    (*dPtr)->points->Add(pManaged);

}

//void* PointList::getManagedPtr() {
//    if (dPtr == nullptr)
//        return nullptr;
//
//    void* obj = dPtr->getManaged();
//    return obj;
//}
//
//void PointList::releaseManagedPtr() {
//    dPtr->unlock();
//}

std::ostream& ipg_marking_library_wrapper::operator<<(std::ostream& os, const PointList& obj) {
    int size = obj.count();
    for (int i = 0; i < size; ++i)
        os << obj.element(i) << std::endl;
    return os;
}
