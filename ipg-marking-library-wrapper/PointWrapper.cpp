#using "ipg/IpgMarkingGraphicsLibrary.dll"

#include "stdafx.h"
#include <msclr/gcroot.h>

#include "PointWrapper.h"
#include "Point.h"

using namespace System;
using namespace System::Runtime::InteropServices;
namespace ipgml = IpgMarkingGraphicsLibrary;

using namespace ipg_marking_library_wrapper;


class ipg_marking_library_wrapper::PointWrapperPrivate {
public:
    msclr::gcroot<ipgml::Point^> _p;
};


PointWrapper::PointWrapper(POINTWRAPPER_HANDLE_PTR ptr) : dPtr(nullptr) {

    if (ptr == nullptr)
        return;
    this->dPtr = new PointWrapperPrivate();
    IntPtr pointer(ptr);
    GCHandle handle = GCHandle::FromIntPtr(pointer);
    ipgml::Point^ obj = (ipgml::Point^) handle.Target;
    //this->dPtr->_p = gcnew ipgml::Point();// obj;// gcnew ipgml::Point(obj);
    //this->dPtr->_p.reset(obj);
    this->dPtr->_p = obj;

}

PointWrapper::PointWrapper(PointWrapper && other) {
    this->dPtr = other.dPtr;
    other.dPtr = nullptr;
}

PointWrapper::~PointWrapper() {
    delete dPtr;
}

PointWrapper& PointWrapper::operator=(PointWrapper&& other) {
    if (&other == this)
        return *this;
    delete dPtr;
    this->dPtr = other.dPtr;
    other.dPtr = nullptr;
    return *this;
}

Point PointWrapper::clone() {
    GCHandle handle = GCHandle::Alloc(dPtr->_p);
    POINTWRAPPER_HANDLE_PTR ptr = GCHandle::ToIntPtr(handle).ToPointer();
    Point clonedPoint(ptr);
    handle.Free();
    return clonedPoint;
}

float PointWrapper::getX() const {
    return dPtr->_p->X;
}

void PointWrapper::setX(float x) {
    //ipgml::Point^ test = dPtr->_p.get();
    ipgml::Point^ test = dPtr->_p;
    dPtr->_p->X = x;
}

float PointWrapper::getY() const {
    return dPtr->_p->Y;
}

void PointWrapper::setY(float y) {
    dPtr->_p->Y = y;
}

float PointWrapper::getZ() const {
    return dPtr->_p->Z;
}

void PointWrapper::setZ(float z) {
    dPtr->_p->Z = z;
}

std::ostream& ipg_marking_library_wrapper::operator<<(std::ostream& os, const PointWrapper& obj) {
    if (obj.dPtr == nullptr)
        return os << "PointWrapper not initialized";
    return os << "PointWrapper (" << obj.getX() << "; " << obj.getY() << ")";
}
