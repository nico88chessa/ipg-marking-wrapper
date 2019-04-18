#using "ipg/IpgMarkingGraphicsLibrary.dll"

#include "stdafx.h"
#include <msclr/auto_gcroot.h>
#include <msclr/gcroot.h>

#include "Point.h"
#include "PointWrapper.h"

using namespace System;
using namespace System::Runtime::InteropServices;
namespace ipgml = IpgMarkingGraphicsLibrary;

using namespace ipg_marking_library_wrapper;


//#define __GCHANDLE_TO_VOIDPTR(x) ((GCHandle::operator System::IntPtr(x)).ToPointer())
//#define __VOIDPTR_TO_GCHANDLE(x) (GCHandle::operator GCHandle(System::IntPtr(x)))

class ipg_marking_library_wrapper::PointPrivate {
public:
    //msclr::auto_gcroot<ipgml::Point^> _p;
    //GCHandle handle;

    /* uso il puntatore perche' devo scambiarmi l'oggetto fra le classi friend;
     * auto_gcroot (wrapper di gcroot) ha il concetto di owner dell'oggetto
     * gcroot (wrapper di GCHandle) non ha il concetto di owner, pero' non mi permette
     * di accedere al puntatore;
     * uso direttametne GCHandle
     */
    POINT_HANDLER handler;
    

public:
    PointPrivate() {
        //_p = gcnew ipgml::Point();
        handler = GCHandle::ToIntPtr(GCHandle::Alloc(gcnew ipgml::Point())).ToPointer();
    }

    PointPrivate(ipgml::Point^ other) {
        //_p.reset((ipgml::Point^)other->Clone());
        handler = GCHandle::ToIntPtr(GCHandle::Alloc(other->Clone())).ToPointer();
    }

    PointPrivate(float x, float y) {
        //_p = gcnew ipgml::Point(x, y);
        handler = GCHandle::ToIntPtr(GCHandle::Alloc(gcnew ipgml::Point(x, y))).ToPointer();
    }

    PointPrivate(float x, float y, float z) {
        //_p = gcnew ipgml::Point(x, y, z);
        handler = GCHandle::ToIntPtr(GCHandle::Alloc(gcnew ipgml::Point(x, y, z))).ToPointer();
    }

    ~PointPrivate() {
        GCHandle h = GCHandle::FromIntPtr(IntPtr(handler));
        delete GCHandle::FromIntPtr(IntPtr(handler)).Target;
        handler = nullptr;
        h.Free();
    }

    ipgml::Point^ operator->() const {
        return static_cast<ipgml::Point^>(GCHandle::FromIntPtr(IntPtr(handler)).Target);
    }

    ipgml::Point^ get() const {
        return static_cast<ipgml::Point^>(GCHandle::FromIntPtr(IntPtr(handler)).Target);
    }

    //void* getManaged() {
    //    if (!handle.IsAllocated)
    //        handle = GCHandle::Alloc(_p.get());
    //    IntPtr t(GCHandle::ToIntPtr(handle));
    //    void* obj = t.ToPointer();
    //    return obj;
    //}

    //void unlock() {
    //    if (handle.IsAllocated)
    //        handle.Free();
    //}

};


Point::Point(POINT_HANDLER obj) {
    if (obj == nullptr)
        return;

    GCHandle handle = GCHandle::FromIntPtr(IntPtr(obj));
    ipgml::Point^ p = (ipgml::Point^) handle.Target;
    this->dPtr = new PointPrivate(p);
}

CONST_POINT_HANDLER Point::getManagedPtr() const {
    if (dPtr == nullptr)
        return nullptr;

    return dPtr->handler;
}

Point::Point() {
    dPtr = new PointPrivate();
}

Point::Point(const Point& other) {
    //ipgml::Point^ p = (ipgml::Point^) GCHandle::FromIntPtr(IntPtr(other.dPtr->handler)).Target;
    ipgml::Point^ p = other.dPtr->get();
    dPtr = new PointPrivate(p);
}

Point::Point(Point&& other) {
    this->dPtr = other.dPtr;
    other.dPtr = nullptr;
}

//Point::Point(void* other) {
//    IntPtr pointer(other);
//    GCHandle handle = GCHandle::FromIntPtr(pointer);
//    ipgml::Point^ obj = (ipgml::Point^) handle.Target;
//    this->dPtr = new PointPrivate(obj);
//}

Point::Point(float x, float y) {
    dPtr = new PointPrivate(x, y);
}

Point::Point(float x, float y, float z) {
    dPtr = new PointPrivate(x, y, z);
}

Point::~Point() {
    delete dPtr;
}

Point& Point::operator=(const Point& other) {

    if (&other == this)
        return *this;

    delete dPtr;
    ipgml::Point^ oPoint = other.dPtr->get();
    dPtr = new PointPrivate(oPoint);
    return *this;
}

Point& Point::operator=(Point&& other) {
    if (this == &other)
        return *this;
    delete dPtr;
    this->dPtr = other.dPtr;
    other.dPtr = nullptr;
    return *this;
}

Point::operator PointWrapper () const {
    return PointWrapper(const_cast<POINT_HANDLER>(this->getManagedPtr()));
}

float Point::getX() const {
    //ipgml::Point^ p = (ipgml::Point^) GCHandle::FromIntPtr(IntPtr(other.dPtr->handler)).Target;
    //return dPtr->get
    return (*dPtr)->X;
}

void Point::setX(float x) {
    (*dPtr)->X = x;
    //dPtr->_p->X = x;
}

float Point::getY() const {
    return (*dPtr)->Y;
    //return dPtr->_p->Y;
}

void Point::setY(float y) {
    //dPtr->_p->Y = y;
    (*dPtr)->Y = y;
}

float Point::getZ() const {
    return (*dPtr)->Z;
    //return dPtr->_p->Z;
}

void Point::setZ(float z) {
    (*dPtr)->Z = z;
    //dPtr->_p->Z = z;
}

//void Point::releaseManagedPtr() {
    //dPtr->unlock();
//}

//void Point::collect() {
//    System::GC::AddMemoryPressure(10000000);
//    System::GC::Collect();
//    System::GC::RemoveMemoryPressure(10000000);
//    
//}

std::ostream& ipg_marking_library_wrapper::operator<<(std::ostream& os, const Point& obj) {
    return os << "Point (" << obj.getX() << "; " << obj.getY() << ")";
}
