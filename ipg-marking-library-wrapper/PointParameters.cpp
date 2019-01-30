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
    msclr::auto_gcroot<ipgml::PointParameters^> _pp;
    GCHandle handle;

public:
    PointParametersPrivate() { }

    PointParametersPrivate(unsigned int v) {
        _pp = gcnew ipgml::PointParameters(v);
    }

    ~PointParametersPrivate() { }

    void* getManaged() {
        if (!handle.IsAllocated)
            handle = GCHandle::Alloc(_pp.get());
        void* obj = GCHandle::ToIntPtr(handle).ToPointer();
        return obj;
    }

    void unlock() {
        if (handle.IsAllocated)
            handle.Free();
    }

};


PointParameters::PointParameters() {
    this->dPtr = new PointParametersPrivate();
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
    dPtr->_pp->AddLaserEntry(dwell, width, powerPercent, count);
}

void PointParameters::clearLaserEntries() {
    dPtr->_pp->ClearLaserEntries();
}

float PointParameters::getLinkError() {
    return dPtr->_pp->LinkError;
}

void PointParameters::setLinkError(float v) {
    dPtr->_pp->LinkError = v;
}

float PointParameters::getLinkRate() {
    return dPtr->_pp->LinkRate;
}

void PointParameters::setLinkRate(float v) {
    dPtr->_pp->LinkRate = v;
}

float PointParameters::getLinkSettleTc() {
    return dPtr->_pp->LinkSettleTc;
}

void PointParameters::setLinkSettleTc(float v) {
    dPtr->_pp->LinkSettleTc = v;
}

int PointParameters::getMode() {
    return dPtr->_pp->Mode;
}

void PointParameters::setMode(int v) {
    dPtr->_pp->Mode = v;
}

float PointParameters::getVelocity() {
    return dPtr->_pp->Velocity;
}

void PointParameters::setVelocity(float v) {
    dPtr->_pp->Velocity = v;
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
