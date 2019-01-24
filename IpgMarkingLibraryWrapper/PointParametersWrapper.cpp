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


PointParametersWrapper::PointParametersWrapper(void * ptr) {
    IntPtr pointer(ptr);
    GCHandle handle = GCHandle::FromIntPtr(pointer);
    ipgml::PointParameters^ obj = (ipgml::PointParameters^)handle.Target;
    this->dPtr = new PointParametersWrapperPrivate();
    this->dPtr->_pp = obj;
}

PointParametersWrapper::~PointParametersWrapper() {
    delete this->dPtr;
}

void PointParametersWrapper::addLaserEntry(float dwell, float width, float powerPercent, int count) {
    dPtr->_pp->AddLaserEntry(dwell, width, powerPercent, count);
}

void PointParametersWrapper::clearLaserEntries() {
    dPtr->_pp->ClearLaserEntries();
}

float PointParametersWrapper::getLinkError() {
    return dPtr->_pp->LinkError;
}

void PointParametersWrapper::setLinkError(float v) {
    dPtr->_pp->LinkError = v;
}

float PointParametersWrapper::getLinkRate() {
    return dPtr->_pp->LinkRate;
}

void PointParametersWrapper::setLinkRate(float v) {
    dPtr->_pp->LinkRate = v;
}

float PointParametersWrapper::getLinkSettleTc() {
    return dPtr->_pp->LinkSettleTc;
}

void PointParametersWrapper::setLinkSettleTc(float v) {
    dPtr->_pp->LinkSettleTc = v;
}

int PointParametersWrapper::getMode() {
    return dPtr->_pp->Mode;
}

void PointParametersWrapper::setMode(int v) {
    dPtr->_pp->Mode = v;
}

float PointParametersWrapper::getVelocity() {
    return dPtr->_pp->Velocity;
}

void PointParametersWrapper::setVelocity(float v) {
    dPtr->_pp->Velocity = v;
}