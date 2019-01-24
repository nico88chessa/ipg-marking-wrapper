#using "ipg/IpgMarkingGraphicsLibrary.dll"

#include "stdafx.h"
#include <msclr/gcroot.h>

#include "PointWrapper.h"

using namespace System;
using namespace System::Runtime::InteropServices;
namespace ipgml = IpgMarkingGraphicsLibrary;

using namespace ipg_marking_library_wrapper;

class ipg_marking_library_wrapper::PointWrapperPrivate {
public:
    msclr::gcroot<ipgml::Point^> _p;
};

PointWrapper::PointWrapper(void* ptr) {

    IntPtr pointer(ptr);
    GCHandle handle = GCHandle::FromIntPtr(pointer);
    ipgml::Point^ obj = (ipgml::Point^)handle.Target;
    this->dPtr = new PointWrapperPrivate();
    this->dPtr->_p = obj;

}


PointWrapper::~PointWrapper() {
    delete dPtr;
}

float PointWrapper::getX() const {
    return dPtr->_p->X;
}

void PointWrapper::setX(float x) {
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