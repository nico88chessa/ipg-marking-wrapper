#using "ipg/IpgMarkingGraphicsLibrary.dll"

#include "stdafx.h"
#include <msclr/auto_gcroot.h>

#include "Point.h"

using namespace System;
using namespace System::Runtime::InteropServices;
namespace ipgml = IpgMarkingGraphicsLibrary;

using namespace ipg_marking_library_wrapper;


class ipg_marking_library_wrapper::PointPrivate {
public:
    msclr::auto_gcroot<ipgml::Point^> _p;
    GCHandle handle;

public:
    PointPrivate() {
        _p = gcnew ipgml::Point();
    }

    PointPrivate(ipgml::Point^ other) {
        _p.reset((ipgml::Point^)other->Clone());
    }

    PointPrivate(float x, float y) {
        _p = gcnew ipgml::Point(x, y);
    }

    PointPrivate(float x, float y, float z) {
        _p = gcnew ipgml::Point(x, y, z);
    }

    ~PointPrivate() {
        unlock();
    }

    void* getManaged() {
        if (!handle.IsAllocated)
            handle = GCHandle::Alloc(_p.get());
        IntPtr t(GCHandle::ToIntPtr(handle));
        void* obj = t.ToPointer();
        return obj;
    }

    void unlock() {
        if (handle.IsAllocated)
            handle.Free();
    }

};


Point::Point() {
    dPtr = new PointPrivate();
}

Point::Point(const Point & other) {
    dPtr = new PointPrivate(other.dPtr->_p.get());
}

Point::Point(void* other) {
    IntPtr pointer(other);
    GCHandle handle = GCHandle::FromIntPtr(pointer);
    ipgml::Point^ obj = (ipgml::Point^) handle.Target;
    this->dPtr = new PointPrivate(obj);
}

Point::Point(float x, float y) {
    dPtr = new PointPrivate(x, y);
}

Point::Point(float x, float y, float z) {
    dPtr = new PointPrivate(x, y, z);
}

Point::Point(Point && other) {
    this->dPtr = other.dPtr;
    other.dPtr = nullptr;
}

Point::~Point() {
    delete dPtr;
}

Point& Point::operator=(const Point& other) {

    ipgml::Point^ clonedPoint = (ipgml::Point^)other.dPtr->_p->Clone();
    this->dPtr->_p.reset(clonedPoint);
    return *this;
}

float Point::getX() const {
    return dPtr->_p->X;
}

void Point::setX(float x) {
    dPtr->_p->X = x;
}

float Point::getY() const {
    return dPtr->_p->Y;
}

void Point::setY(float y) {
    dPtr->_p->Y = y;
}

float Point::getZ() const {
    return dPtr->_p->Z;
}

void Point::setZ(float z) {
    dPtr->_p->Z = z;
}

void* Point::getManagedPtr() {
    
    if (dPtr == nullptr)
        return nullptr;

    void* obj = dPtr->getManaged();
    return obj;
    
}

void Point::releaseManagedPtr() {
    dPtr->unlock();
}

//void Point::collect() {
//    System::GC::AddMemoryPressure(10000000);
//    System::GC::Collect();
//    System::GC::RemoveMemoryPressure(10000000);
//    
//}

std::ostream& ipg_marking_library_wrapper::operator<<(std::ostream& os, const Point& obj) {
    return os << "Point (" << obj.getX() << "; " << obj.getY() << ")";
}