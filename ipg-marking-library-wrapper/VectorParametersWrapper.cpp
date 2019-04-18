#using "ipg/IpgMarkingGraphicsLibrary.dll"

#include "stdafx.h"
#include <msclr/gcroot.h>

#include "VectorParametersWrapper.h"

using namespace System;
using namespace System::Runtime::InteropServices;
namespace ipgml = IpgMarkingGraphicsLibrary;

using namespace ipg_marking_library_wrapper;

class ipg_marking_library_wrapper::VectorParametersWrapperPrivate {
public:
    msclr::gcroot<ipgml::VectorParameters^> _vp;
};

VectorParametersWrapper::VectorParametersWrapper(HANDLE_PTR ptr) : dPtr(nullptr) {
    if (ptr == nullptr)
        return;
    this->dPtr = new VectorParametersWrapperPrivate();
    IntPtr pointer(ptr);
    GCHandle handle = GCHandle::FromIntPtr(pointer);
    ipgml::VectorParameters^ obj = (ipgml::VectorParameters^) handle.Target;
    this->dPtr->_vp = obj;
}

VectorParametersWrapper::VectorParametersWrapper(VectorParametersWrapper&& other) {
    this->dPtr = other.dPtr;
    other.dPtr = nullptr;
}

VectorParametersWrapper::~VectorParametersWrapper() {
    delete dPtr;
}

VectorParametersWrapper& VectorParametersWrapper::operator=(VectorParametersWrapper && other) {
    if (&other == this)
        return *this;
    delete dPtr;
    this->dPtr = other.dPtr;
    other.dPtr = nullptr;
    return *this;
}

void VectorParametersWrapper::addLaserEntry(float velocity, float frequency, float pulseWidth, float powerPercent) {
    if (dPtr == nullptr)
        return;
    dPtr->_vp->AddLaserEntry(velocity, frequency, pulseWidth, powerPercent);
}

void VectorParametersWrapper::clearLaserEntries() {
    if (dPtr == nullptr)
        return;
    dPtr->_vp->ClearLaserEntries();
}

float VectorParametersWrapper::getEndVelocity() {
    if (dPtr == nullptr)
        return 0.0f;
    return dPtr->_vp->EndVelocity;
}

void VectorParametersWrapper::setEndVelocity(float value) {
    if (dPtr == nullptr)
        return;
    dPtr->_vp->EndVelocity = value;
}

float VectorParametersWrapper::getLaserOnAdjust() {
    if (dPtr == nullptr)
        return 0.0f;
    return dPtr->_vp->LaserOnAdjust;
}

void VectorParametersWrapper::setLaserOnAdjust(float value) {
    if (dPtr == nullptr)
        return;
    dPtr->_vp->LaserOnAdjust = value;
}

float VectorParametersWrapper::getLinkRate() {
    if (dPtr == nullptr)
        return 0.0f;
    return dPtr->_vp->LinkRate;
}

void VectorParametersWrapper::setLinkRate(float value) {
    if (dPtr == nullptr)
        return;
    dPtr->_vp->LinkRate = value;
}

float VectorParametersWrapper::getLinkSettleTc() {
    if (dPtr == nullptr)
        return 0.0f;
    return dPtr->_vp->LinkSettleTc;
}

void VectorParametersWrapper::setLinkSettleTc(float value) {
    if (dPtr == nullptr)
        return;
    dPtr->_vp->LinkSettleTc = value;
}

float VectorParametersWrapper::getMaxAccelRatio() {
    if (dPtr == nullptr)
        return 0.0f;
    return dPtr->_vp->MaxAccelRatio;
}

void VectorParametersWrapper::setMaxAccelRatio(float value) {
    if (dPtr == nullptr)
        return;
    dPtr->_vp->MaxAccelRatio = value;
}

float VectorParametersWrapper::getMaxRadialError() {
    if (dPtr == nullptr)
        return 0.0f;
    return dPtr->_vp->MaxRadialError;
}

void VectorParametersWrapper::setMaxRadialError(float value) {
    if (dPtr == nullptr)
        return;
    dPtr->_vp->MaxRadialError = value;
}

float VectorParametersWrapper::getMidVelocity() {
    if (dPtr == nullptr)
        return 0.0f;
    return dPtr->_vp->MidVelocity;
}

void VectorParametersWrapper::setMidVelocity(float value) {
    if (dPtr == nullptr)
        return;
    return dPtr->_vp->MidVelocity = value;

}

int VectorParametersWrapper::getMode() {
    if (dPtr == nullptr)
        return 0;
    return dPtr->_vp->Mode;
}

void VectorParametersWrapper::setMode(int value) {
    if (dPtr == nullptr)
        return;
    dPtr->_vp->Mode = value;
}

float VectorParametersWrapper::getVertexSettleTc() {
    if (dPtr == nullptr)
        return 0.0f;
    return dPtr->_vp->VertexSettleTc;
}

void VectorParametersWrapper::setVertexSettleTc(float value) {
    if (dPtr == nullptr)
        return;
    dPtr->_vp->VertexSettleTc = value;
}