#using "ipg/IpgMarkingGraphicsLibrary.dll"

#include "stdafx.h"
#include <msclr/gcroot.h>

#include "PointParametersWrapper.h"

using namespace System;
using namespace System::Runtime::InteropServices;
namespace ipgml = IpgMarkingGraphicsLibrary;

using namespace ipg_marking_library_wrapper;

class ipg_marking_library_wrapper::PointParametersWrapperPrivate {
public:
    msclr::gcroot<ipgml::PointParameters^> _pp;
};


PointParametersWrapper::PointParametersWrapper(POINT_PARAMETERS_WRAPPER_HANDLE_PTR ptr) : dPtr(nullptr) {
    if (ptr == nullptr)
        return;
    this->dPtr = new PointParametersWrapperPrivate();
    IntPtr pointer(ptr);
    GCHandle handle = GCHandle::FromIntPtr(pointer);
    ipgml::PointParameters^ obj = (ipgml::PointParameters^) handle.Target;
    this->dPtr->_pp = obj;
}

PointParametersWrapper::PointParametersWrapper(PointParametersWrapper&& other) {
    this->dPtr = other.dPtr;
    other.dPtr = nullptr;
}

PointParametersWrapper::~PointParametersWrapper() {
    delete dPtr;
}

PointParametersWrapper& PointParametersWrapper::operator=(PointParametersWrapper&& other) {
    if (&other == this)
        return *this;
    delete dPtr;
    this->dPtr = other.dPtr;
    other.dPtr = nullptr;
    return *this;
}

void PointParametersWrapper::addLaserEntry(float dwell, float width, float powerPercent, int count) {
    if (dPtr == nullptr)
        return;
    dPtr->_pp->AddLaserEntry(dwell, width, powerPercent, count);
}

void PointParametersWrapper::clearLaserEntries() {
    if (dPtr == nullptr)
        return;
    dPtr->_pp->ClearLaserEntries();
}

float PointParametersWrapper::getLinkError() {
    if (dPtr == nullptr)
        return 0.0f;
    return dPtr->_pp->LinkError;
}

void PointParametersWrapper::setLinkError(float v) {
    if (dPtr == nullptr)
        return;
    dPtr->_pp->LinkError = v;
}

float PointParametersWrapper::getLinkRate() {
    if (dPtr == nullptr)
        return 0.0f;
    return dPtr->_pp->LinkRate;
}

void PointParametersWrapper::setLinkRate(float v) {
    if (dPtr == nullptr)
        return;
    dPtr->_pp->LinkRate = v;
}

float PointParametersWrapper::getLinkSettleTc() {
    if (dPtr == nullptr)
        return 0.0f;
    return dPtr->_pp->LinkSettleTc;
}

void PointParametersWrapper::setLinkSettleTc(float v) {
    if (dPtr == nullptr)
        return;
    dPtr->_pp->LinkSettleTc = v;
}

int PointParametersWrapper::getMode() {
    if (dPtr == nullptr)
        return 0;
    return dPtr->_pp->Mode;
}

void PointParametersWrapper::setMode(int v) {
    if (dPtr == nullptr)
        return;
    dPtr->_pp->Mode = v;
}

float PointParametersWrapper::getVelocity() {
    if (dPtr == nullptr)
        return 0.0f;
    return dPtr->_pp->Velocity;
}

void PointParametersWrapper::setVelocity(float v) {
    if (dPtr == nullptr)
        return;
    dPtr->_pp->Velocity = v;
}