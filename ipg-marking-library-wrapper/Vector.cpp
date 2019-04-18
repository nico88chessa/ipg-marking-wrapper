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
    /*msclr::auto_gcroot<ipgml::Vector^> _v;
    GCHandle handle;*/
    VECTOR_HANDLER handler;

public:
    VectorPrivate() {
        //_v = gcnew ipgml::Vector();
        handler = GCHandle::ToIntPtr(GCHandle::Alloc(gcnew ipgml::Vector())).ToPointer();
    }

    VectorPrivate(ipgml::Point^ start, ipgml::Point^ end) {
        //_v = gcnew ipgml::Vector(start, end);
        handler = GCHandle::ToIntPtr(GCHandle::Alloc(gcnew ipgml::Vector(start, end))).ToPointer();
    }
    
    VectorPrivate(ipgml::Vector^ other) {
        //_v.reset((ipgml::Vector^) other->Clone());
        handler = GCHandle::ToIntPtr(GCHandle::Alloc(other->Clone())).ToPointer();
    }

    ~VectorPrivate() {
        GCHandle h = GCHandle::FromIntPtr(IntPtr(handler));
        delete GCHandle::FromIntPtr(IntPtr(handler)).Target;
        handler = nullptr;
        h.Free();
    }

    ipgml::Vector^ operator->() const {
        return static_cast<ipgml::Vector^>(GCHandle::FromIntPtr(IntPtr(handler)).Target);
    }

    ipgml::Vector^ get() const {
        return static_cast<ipgml::Vector^>(GCHandle::FromIntPtr(IntPtr(handler)).Target);
    }

    //void* getManaged() {
    //    if (!handle.IsAllocated)
    //        handle = GCHandle::Alloc(_v.get());
    //    IntPtr t(GCHandle::ToIntPtr(handle));
    //    void* obj = t.ToPointer();
    //    return obj;
    //}

    //void unlock() {
    //    if (handle.IsAllocated)
    //        handle.Free();
    //}

};


Vector::Vector(VECTOR_HANDLER obj) {
    if (obj == nullptr)
        return;

    GCHandle handle = GCHandle::FromIntPtr(IntPtr(obj));
    ipgml::Vector^ v = (ipgml::Vector^) handle.Target;
    this->dPtr = new VectorPrivate(v);
}

CONST_VECTOR_HANDLER ipg_marking_library_wrapper::Vector::getManagedPtr() const {
    if (dPtr == nullptr)
        return nullptr;

    return dPtr->handler;
}

Vector::Vector() {
    dPtr = new VectorPrivate();
}

Vector::Vector(const Vector& other) {
    ipgml::Vector^ v = other.dPtr->get();
    dPtr = new VectorPrivate(v);
}

Vector::Vector(Vector&& other) {
    this->dPtr = other.dPtr;
    other.dPtr = nullptr;
}

//Vector::Vector(void* other) {
//    IntPtr pointer(other);
//    GCHandle handle = GCHandle::FromIntPtr(pointer);
//    ipgml::Vector^ obj = (ipgml::Vector^) handle.Target;
//    this->dPtr = new VectorPrivate(obj);
//}

Vector::Vector(const Point& start, const Point& end) {

    Point startLocal(start);
    Point endLocal(end);
    
    /*GCHandle hStartPoint = GCHandle::FromIntPtr(IntPtr(startLocal.getManagedPtr()));
    ipgml::Point^ startManaged = (ipgml::Point^)hStartPoint.Target;
    GCHandle hEndPoint = GCHandle::FromIntPtr(IntPtr(endLocal.getManagedPtr()));
    ipgml::Point^ endManaged = (ipgml::Point^)hEndPoint.Target;*/

    //dPtr = new VectorPrivate(startManaged, endManaged);

    //startLocal.releaseManagedPtr();
    //endLocal.releaseManagedPtr();

}

Vector::~Vector() {
    delete dPtr;
}

Vector& Vector::operator=(const Vector & other) {
    if (&other == this)
        return *this;

    delete dPtr;
    ipgml::Vector^ v = other.dPtr->get();
    dPtr = new VectorPrivate(v);
    return *this;
}

float Vector::getLength() const {
    if (dPtr == nullptr)
        return 0.0f;

    return (*dPtr)->Length;
}

PointWrapper Vector::getStart() const {
    if (dPtr == nullptr)
        return PointWrapper();

    ipgml::Point^ p = (*dPtr)->Start;
    GCHandle handle = GCHandle::Alloc(p);
    PointWrapper res(GCHandle::ToIntPtr(handle).ToPointer());
    handle.Free();
    return res;
}

void Vector::setStart(const Point& start) {
    if (dPtr == nullptr)
        return;

    GCHandle hStartPoint = GCHandle::FromIntPtr(IntPtr(const_cast<POINT_HANDLER>(start.getManagedPtr())));
    ipgml::Point^ startManaged = (ipgml::Point^) hStartPoint.Target;
    (*dPtr)->Start = startManaged;
}

PointWrapper Vector::getEnd() const {

    if (dPtr == nullptr)
        return PointWrapper();

    ipgml::Point^ p = (*dPtr)->End;
    GCHandle handle = GCHandle::Alloc(p);
    PointWrapper res(GCHandle::ToIntPtr(handle).ToPointer());
    handle.Free();
    return res;
}

void Vector::setEnd(const Point& end) {
    if (dPtr == nullptr)
        return;

    GCHandle hEndPoint = GCHandle::FromIntPtr(IntPtr(const_cast<POINT_HANDLER>(end.getManagedPtr())));
    ipgml::Point^ endManaged = (ipgml::Point^) hEndPoint.Target;
    (*dPtr)->End = endManaged;
}

//void* Vector::getManagedPtr() {
//    
//    if (dPtr == nullptr)
//        return nullptr;
//
//    void* obj = dPtr->getManaged();
//    return obj;
//    
//}
//
//void Vector::releaseManagedPtr() {
//    dPtr->unlock();
//}

int Vector::getPointsPerVector() {
    return ipgml::Vector::PointsPerVector;
}

std::ostream& ipg_marking_library_wrapper::operator<<(std::ostream& os, const Vector & obj) {
    PointWrapper start = obj.getStart();
    PointWrapper end = obj.getEnd();
    /*return os << "Vector Start (" << start.getX() << "; " << start.getY() << ") - " << \
        "End (" << end.getX() << "; " << end.getY() << ")" << std::endl;*/
    return os << "Start " << start << " - End " << end;
}
