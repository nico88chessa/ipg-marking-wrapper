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
    msclr::auto_gcroot<ipgml::OutputPointsProperties^> _outputPointProperties;
    GCHandle handle;

public:
    OutputPointsPropertiesPrivate(float pulseEnergy) {
        _outputPointProperties = gcnew ipgml::OutputPointsProperties(pulseEnergy);
        handle = GCHandle::Alloc(_outputPointProperties);
    }
    OutputPointsPropertiesPrivate(float pulseEnergy, ipgml::Optimization opt) {
        _outputPointProperties = gcnew ipgml::OutputPointsProperties(pulseEnergy, opt);
        handle = GCHandle::Alloc(_outputPointProperties);
    }
    OutputPointsPropertiesPrivate(ipgml::OutputPointsProperties^ other) {
        _outputPointProperties = other;
        handle = GCHandle::Alloc(other);
    }
    ~OutputPointsPropertiesPrivate() {
        handle.Free();
    }
};


OutputPointsProperties::OutputPointsProperties(void* other) {
    IntPtr pointer(other);
    GCHandle handle = GCHandle::FromIntPtr(pointer);
    ipgml::OutputPointsProperties^ obj = (ipgml::OutputPointsProperties^)handle.Target;
    this->dPtr = new OutputPointsPropertiesPrivate(obj);
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
    switch (dPtr->_outputPointProperties->Opt) {
    case ipgml::Optimization::Default: opt = Optimization::DEFAULT; break;
    case ipgml::Optimization::Quality: opt = Optimization::QUALITY; break;
    case ipgml::Optimization::Speed: opt = Optimization::SPEED; break;
    }
    return opt;
}

float OutputPointsProperties::getPulseEnergy() const {
    if (dPtr == nullptr)
        return 0.0f;

    return dPtr->_outputPointProperties->PulseEnergy;
}

void* OutputPointsProperties::getManagedObject() {
    if (dPtr == nullptr)
        return nullptr;

    return GCHandle::ToIntPtr(dPtr->handle).ToPointer();

}
