#using "ipg/IpgMarkingGraphicsLibrary.dll"

#include "stdafx.h"
#include <msclr/auto_gcroot.h>

#include "OutputVectorsProperties.h"

using namespace System;
using namespace System::Runtime::InteropServices;
namespace ipgml = IpgMarkingGraphicsLibrary;

using namespace ipg_marking_library_wrapper;

class ipg_marking_library_wrapper::OutputVectorsPropertiesPrivate {
public:
    msclr::auto_gcroot<ipgml::OutputVectorsProperties^> _ovp;
    GCHandle handle;

public:
    OutputVectorsPropertiesPrivate(float pitch, float pulseEnergy) {
        _ovp = gcnew ipgml::OutputVectorsProperties(pitch, pulseEnergy);
        handle = GCHandle::Alloc(_ovp);
    }
    OutputVectorsPropertiesPrivate(float powerWatt, float velocity, float frequency, float pulseWidth, ipgml::Optimization opt) {
        _ovp = gcnew ipgml::OutputVectorsProperties(powerWatt, velocity, frequency, pulseWidth, opt);
        handle = GCHandle::Alloc(_ovp);
    }
    OutputVectorsPropertiesPrivate(float pitch, float pulseEnergy, ipgml::Optimization opt) {
        _ovp = gcnew ipgml::OutputVectorsProperties(pitch, pulseEnergy, opt);
        handle = GCHandle::Alloc(_ovp);
    }
    OutputVectorsPropertiesPrivate(float pitch, float pulseEnergy, ipgml::Optimization opt, float frequency) {
        _ovp = gcnew ipgml::OutputVectorsProperties(pitch, pulseEnergy, opt, frequency);
        handle = GCHandle::Alloc(_ovp);
    }
    OutputVectorsPropertiesPrivate(ipgml::OutputVectorsProperties^ other) {
        _ovp = other;
        handle = GCHandle::Alloc(other);
    }
    ~OutputVectorsPropertiesPrivate() {
        handle.Free();
    }
};

OutputVectorsProperties::OutputVectorsProperties(float pitch, float pulseEnergy) {
    this->dPtr = new OutputVectorsPropertiesPrivate(pitch, pulseEnergy);
}

OutputVectorsProperties::OutputVectorsProperties(float powerWatt, float velocity, float frequency, float pulseWidth, Optimization opt) {

    ipgml::Optimization o;
    switch (opt) {
    case Optimization::DEFAULT: o = ipgml::Optimization::Default; break;
    case Optimization::QUALITY: o = ipgml::Optimization::Quality; break;
    case Optimization::SPEED: o = ipgml::Optimization::Speed; break;
    }

    this->dPtr = new OutputVectorsPropertiesPrivate(powerWatt, velocity, frequency, pulseWidth, o);
}

OutputVectorsProperties::OutputVectorsProperties(float pitch, float pulseEnergy, Optimization opt) {
    ipgml::Optimization o;
    switch (opt) {
    case Optimization::DEFAULT: o = ipgml::Optimization::Default; break;
    case Optimization::QUALITY: o = ipgml::Optimization::Quality; break;
    case Optimization::SPEED: o = ipgml::Optimization::Speed; break;
    }

    this->dPtr = new OutputVectorsPropertiesPrivate(pitch, pulseEnergy, o);
}

OutputVectorsProperties::OutputVectorsProperties(float pitch, float pulseEnergy, Optimization opt, float frequency) {
    ipgml::Optimization o;
    switch (opt) {
    case Optimization::DEFAULT: o = ipgml::Optimization::Default; break;
    case Optimization::QUALITY: o = ipgml::Optimization::Quality; break;
    case Optimization::SPEED: o = ipgml::Optimization::Speed; break;
    }

    this->dPtr = new OutputVectorsPropertiesPrivate(pitch, pulseEnergy, o, frequency);
}

OutputVectorsProperties::OutputVectorsProperties(void* other) {
    IntPtr pointer(other);
    GCHandle handle = GCHandle::FromIntPtr(pointer);
    ipgml::OutputVectorsProperties^ obj = (ipgml::OutputVectorsProperties^)handle.Target;
    this->dPtr = new OutputVectorsPropertiesPrivate(obj);
}

OutputVectorsProperties::OutputVectorsProperties(OutputVectorsProperties&& other) {
    this->dPtr = other.dPtr;
    other.dPtr = nullptr;
}

OutputVectorsProperties::~OutputVectorsProperties() {
    delete dPtr;
}

float OutputVectorsProperties::getFrequency() const {
    return dPtr->_ovp->Frequency;
}

Optimization OutputVectorsProperties::getOptimization() const {
    Optimization opt;
    ipgml::Optimization o = this->dPtr->_ovp->Opt;
    switch (o) {
        case ipgml::Optimization::Default: opt = Optimization::DEFAULT; break;
        case ipgml::Optimization::Quality: opt = Optimization::QUALITY; break;
        case ipgml::Optimization::Speed: opt = Optimization::SPEED; break;
    }
    return opt;
}

float OutputVectorsProperties::getPitch() const {
    return dPtr->_ovp->Pitch;
}

float OutputVectorsProperties::getPulseEnergy() const {
    return dPtr->_ovp->PulseEnergy;
}

float OutputVectorsProperties::getPulseWidth() const {
    return dPtr->_ovp->PulseWidth;
}
