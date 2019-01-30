#using "ipg/IpgMarkingGraphicsLibrary.dll"

#include "stdafx.h"
#include <msclr/auto_gcroot.h>

#include "OutputPointsProperties.h"

using namespace System;
using namespace System::Runtime::InteropServices;
namespace ipgml = IpgMarkingGraphicsLibrary;

using namespace ipg_marking_library_wrapper;

class ipg_marking_library_wrapper::OutputPointsPropertiesPrivate {
public:
    msclr::auto_gcroot<ipgml::OutputPointsProperties^> _opp;
    GCHandle handle;

public:
    OutputPointsPropertiesPrivate() { }

    OutputPointsPropertiesPrivate(float pulseEnergy) {
        _opp = gcnew ipgml::OutputPointsProperties(pulseEnergy);
    }

    OutputPointsPropertiesPrivate(float pulseEnergy, ipgml::Optimization opt) {
        _opp = gcnew ipgml::OutputPointsProperties(pulseEnergy, opt);
    }

    ~OutputPointsPropertiesPrivate() {
        unlock();
    }

    void* getManaged() {
        if (!handle.IsAllocated)
            handle = GCHandle::Alloc(_opp.get());
        void* obj = GCHandle::ToIntPtr(handle).ToPointer();
        return obj;
    }

    void unlock() {
        if (handle.IsAllocated)
            handle.Free();
    }
};


OutputPointsProperties::OutputPointsProperties() {
    dPtr = new OutputPointsPropertiesPrivate();
}

OutputPointsProperties::OutputPointsProperties(float pulseEnergy) {
    dPtr = new OutputPointsPropertiesPrivate(pulseEnergy);
}

OutputPointsProperties::OutputPointsProperties(float pulseEnergy, Optimization opt) {

    ipgml::Optimization _o;
    switch (opt) {
    case Optimization::DEFAULT: _o = ipgml::Optimization::Default; break;
    case Optimization::QUALITY: _o = ipgml::Optimization::Quality; break;
    case Optimization::SPEED: _o = ipgml::Optimization::Speed; break;
    }
    
    dPtr = new OutputPointsPropertiesPrivate(pulseEnergy, _o);

}

OutputPointsProperties::OutputPointsProperties(OutputPointsProperties && other) {
    this->dPtr = other.dPtr;
    other.dPtr = nullptr;
}

OutputPointsProperties::~OutputPointsProperties() {
    delete dPtr;
}

Optimization OutputPointsProperties::getOptimization() const {

    if (dPtr == nullptr)
        return Optimization::DEFAULT;

    Optimization opt;
    switch (dPtr->_opp->Opt) {
    case ipgml::Optimization::Default: opt = Optimization::DEFAULT; break;
    case ipgml::Optimization::Quality: opt = Optimization::QUALITY; break;
    case ipgml::Optimization::Speed: opt = Optimization::SPEED; break;
    }
    return opt;
}

float OutputPointsProperties::getPulseEnergy() const {
    if (dPtr == nullptr)
        return 0.0f;

    return dPtr->_opp->PulseEnergy;
}

void* OutputPointsProperties::getManagedPtr() {
    
    if (dPtr == nullptr)
        return nullptr;

    void* obj = dPtr->getManaged();
    return obj;

}

void OutputPointsProperties::releaseManagedPtr() {
    dPtr->unlock();
}
