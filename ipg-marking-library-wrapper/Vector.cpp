#using "ipg/IpgMarkingGraphicsLibrary.dll"

#include "stdafx.h"
#include <msclr/auto_gcroot.h>

#include "Vector.h"

using namespace System;
using namespace System::Runtime::InteropServices;
namespace ipgml = IpgMarkingGraphicsLibrary;

using namespace ipg_marking_library_wrapper;


class ipg_marking_library_wrapper::VectorPrivate {
public:
    msclr::auto_gcroot<ipgml::Vector^> _v;
    GCHandle handle;

public:
    VectorPrivate() {
        _v = gcnew ipgml::Vector();
    }

    VectorPrivate(ipgml::Point^ start, ipgml::Point^ end) {
        _v = gcnew ipgml::Vector(start, end);
    }
    
    VectorPrivate(ipgml::Vector^ other) {
        _v.reset((ipgml::Vector^) other->Clone());
    }

    ~VectorPrivate() {
        unlock();
    }

    void* getManaged() {
        if (!handle.IsAllocated)
            handle = GCHandle::Alloc(_v.get());
        IntPtr t(GCHandle::ToIntPtr(handle));
        void* obj = t.ToPointer();
        return obj;
    }

    void unlock() {
        if (handle.IsAllocated)
            handle.Free();
    }

};


Vector::Vector() {
    dPtr = new VectorPrivate();
}

Vector::Vector(const Vector& other) {
    dPtr = new VectorPrivate(other.dPtr->_v.get());
}

Vector::Vector(Vector&& other) {
    this->dPtr = other.dPtr;
    other.dPtr = nullptr;
}

Vector::Vector(void* other) {
    IntPtr pointer(other);
    GCHandle handle = GCHandle::FromIntPtr(pointer);
    ipgml::Vector^ obj = (ipgml::Vector^) handle.Target;
    this->dPtr = new VectorPrivate(obj);
}

Vector::Vector(const Point& start, const Point& end) {

    Point startLocal(start);
    Point endLocal(end);
    
    GCHandle hStartPoint = GCHandle::FromIntPtr(IntPtr(startLocal.getManagedPtr()));
    ipgml::Point^ startManaged = (ipgml::Point^)hStartPoint.Target;
    GCHandle hEndPoint = GCHandle::FromIntPtr(IntPtr(endLocal.getManagedPtr()));
    ipgml::Point^ endManaged = (ipgml::Point^)hEndPoint.Target;

    dPtr = new VectorPrivate(startManaged, endManaged);

    startLocal.releaseManagedPtr();
    endLocal.releaseManagedPtr();

}

Vector::~Vector() {
    delete dPtr;
}

Vector& Vector::operator=(const Vector & other) {
    ipgml::Vector^ clonedPoint = (ipgml::Vector^)other.dPtr->_v->Clone();
    this->dPtr->_v.reset(clonedPoint);
    return *this;
}

float Vector::getLength() const {
    if (dPtr == nullptr)
        return 0.0f;

    return dPtr->_v->Length;
}

Point Vector::getStart() const {
    if (dPtr == nullptr)
        return Point();

    ipgml::Point^ p = dPtr->_v->Start;
    GCHandle handle = GCHandle::Alloc(p);
    Point res(GCHandle::ToIntPtr(handle).ToPointer());
    handle.Free();
    return res;
}

void Vector::setStart(const Point& start) {
    if (dPtr == nullptr)
        return;

    Point startLocal(start);
    GCHandle hStartPoint = GCHandle::FromIntPtr(IntPtr(startLocal.getManagedPtr()));
    ipgml::Point^ startManaged = (ipgml::Point^)hStartPoint.Target;
    dPtr->_v->Start = startManaged;
    startLocal.releaseManagedPtr();
}

Point Vector::getEnd() const {
    if (dPtr == nullptr)
        return Point();

    ipgml::Point^ p = dPtr->_v->End;
    GCHandle handle = GCHandle::Alloc(p);
    Point res(GCHandle::ToIntPtr(handle).ToPointer());
    handle.Free();
    return res;
}

void Vector::setEnd(const Point & end) {
    if (dPtr == nullptr)
        return;

    Point endLocal(end);
    GCHandle hEndPoint = GCHandle::FromIntPtr(IntPtr(endLocal.getManagedPtr()));
    ipgml::Point^ endManaged = (ipgml::Point^)hEndPoint.Target;
    dPtr->_v->End = endManaged;
    endLocal.releaseManagedPtr();
}

void* Vector::getManagedPtr() {
    
    if (dPtr == nullptr)
        return nullptr;

    void* obj = dPtr->getManaged();
    return obj;
    
}

void Vector::releaseManagedPtr() {
    dPtr->unlock();
}

int Vector::getPointsPerVector() {
    return ipgml::Vector::PointsPerVector;
}

std::ostream& ipg_marking_library_wrapper::operator<<(std::ostream& os, const Vector & obj) {
    Point& start = obj.getStart();
    Point& end = obj.getEnd();
    /*return os << "Vector Start (" << start.getX() << "; " << start.getY() << ") - " << \
        "End (" << end.getX() << "; " << end.getY() << ")" << std::endl;*/
    return os << "Start " << start << " - End " << end;
}
