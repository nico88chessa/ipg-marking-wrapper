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
    using type = msclr::auto_gcroot<ipgml::Point^>;
    type _point;
    GCHandle handle;

public:
    PointPrivate() {
        _point = gcnew ipgml::Point();
    }
    PointPrivate(ipgml::Point^ other) {
        _point = other;// gcnew ipgml::Point(other);
    }
    PointPrivate(float x, float y) {
        _point = gcnew ipgml::Point(x, y);
    }
    PointPrivate(float x, float y, float z) {
        _point = gcnew ipgml::Point(x, y, z);
    }
    ~PointPrivate() {
    }
    void* getManaged() {
        handle = GCHandle::Alloc(_point.get());
        void* obj = GCHandle::ToIntPtr(handle).ToPointer();
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
    dPtr = new PointPrivate();
    dPtr->_point = other.dPtr->_point;
}

Point::Point(void* other) {
    IntPtr pointer(other);
    GCHandle handle = GCHandle::FromIntPtr(pointer);
    ipgml::Point^ obj = (ipgml::Point^)handle.Target;
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

float Point::getX() const {
    return dPtr->_point->X;
}

void Point::setX(float x) {
    dPtr->_point->X = x;
}

float Point::getY() const {
    return dPtr->_point->Y;
}

void Point::setY(float y) {
    dPtr->_point->Y = y;
}

float Point::getZ() const {
    return dPtr->_point->Z;
}

void Point::setZ(float z) {
    dPtr->_point->Z = z;
}

void* Point::getManagedObject() {
    
    if (dPtr == nullptr)
        return nullptr;

    void* obj = dPtr->getManaged();
    return obj;
    
}

void Point::releaseManagedObject() {

    dPtr->unlock();
    /*GCHandle^ handle = GCHandle::FromIntPtr(IntPtr(objPtr));
    if (handle != nullptr)
        handle->Free();*/

}
