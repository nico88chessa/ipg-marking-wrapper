#using "ipg/IpgMarkingGraphicsLibrary.dll"

#include "stdafx.h"
#include <msclr/auto_gcroot.h>

#include "PointParameters.h"

using namespace System;
using namespace System::Runtime::InteropServices;
namespace ipgml = IpgMarkingGraphicsLibrary;

using namespace ipg_marking_library_wrapper;

class ipg_marking_library_wrapper::PointParametersPrivate {
public:
    msclr::auto_gcroot<ipgml::PointParameters^> _pointParameters;
    GCHandle handle;

public:
    PointParametersPrivate(unsigned int v) {
        _pointParameters = gcnew ipgml::PointParameters(v);
    }
    PointParametersPrivate(ipgml::PointParameters^ other) {
        _pointParameters = other;
    }
    ~PointParametersPrivate() {
    }
    void* getManaged() {
        handle = GCHandle::Alloc(_pointParameters.get());
        void* obj = GCHandle::ToIntPtr(handle).ToPointer();
        return obj;
    }

    void unlock() {
        if (handle.IsAllocated)
            handle.Free();
    }
};


PointParameters::PointParameters(void* other) {
    IntPtr pointer(other);
    GCHandle handle = GCHandle::FromIntPtr(pointer);
    ipgml::PointParameters^ obj = (ipgml::PointParameters^)handle.Target;
    this->dPtr = new PointParametersPrivate(obj);
}

PointParameters::PointParameters(unsigned int v) {
    this->dPtr = new PointParametersPrivate(v);
}

PointParameters::PointParameters(PointParameters&& copy) {
    this->dPtr = copy.dPtr;
    copy.dPtr = nullptr;
}

PointParameters::~PointParameters() {
    delete dPtr;
}

void PointParameters::addLaserEntry(float dwell, float width, float powerPercent, int count) {
    dPtr->_pointParameters->AddLaserEntry(dwell, width, powerPercent, count);
}

void PointParameters::clearLaserEntries() {
    dPtr->_pointParameters->ClearLaserEntries();
}

float PointParameters::getLinkError() {
    return dPtr->_pointParameters->LinkError;
}

void PointParameters::setLinkError(float v) {
    dPtr->_pointParameters->LinkError = v;
}

float PointParameters::getLinkRate() {
    return dPtr->_pointParameters->LinkRate;
}

void PointParameters::setLinkRate(float v) {
    dPtr->_pointParameters->LinkRate = v;
}

float PointParameters::getLinkSettleTc() {
    return dPtr->_pointParameters->LinkSettleTc;
}

void PointParameters::setLinkSettleTc(float v) {
    dPtr->_pointParameters->LinkSettleTc = v;
}

int PointParameters::getMode() {
    return dPtr->_pointParameters->Mode;
}

void PointParameters::setMode(int v) {
    dPtr->_pointParameters->Mode = v;
}

float PointParameters::getVelocity() {
    return dPtr->_pointParameters->Velocity;
}

void PointParameters::setVelocity(float v) {
    dPtr->_pointParameters->Velocity = v;
}

void* PointParameters::getManagedObject() {

    if (dPtr == nullptr)
        return nullptr;

    void* obj = dPtr->getManaged();
    return obj;
}

void PointParameters::releaseManagedObject() {
    dPtr->unlock();
}
