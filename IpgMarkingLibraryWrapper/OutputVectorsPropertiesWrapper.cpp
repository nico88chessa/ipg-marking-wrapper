#using "ipg/IpgMarkingGraphicsLibrary.dll"

#include "stdafx.h"
#include <msclr/gcroot.h>

#include "OutputVectorsPropertiesWrapper.h"

using namespace System;
using namespace System::Runtime::InteropServices;
namespace ipgml = IpgMarkingGraphicsLibrary;

using namespace ipg_marking_library_wrapper;

class ipg_marking_library_wrapper::OutputVectorsPropertiesWrapperPrivate {
public:
    msclr::gcroot<ipgml::OutputVectorsProperties^> _ovp;
};

OutputVectorsPropertiesWrapper::OutputVectorsPropertiesWrapper(void * ptr) {
    IntPtr pointer(ptr);
    GCHandle handle = GCHandle::FromIntPtr(pointer);
    ipgml::OutputVectorsProperties^ obj = (ipgml::OutputVectorsProperties^)handle.Target;
    this->dPtr = new OutputVectorsPropertiesWrapperPrivate();
    this->dPtr->_ovp = obj;
}

OutputVectorsPropertiesWrapper::~OutputVectorsPropertiesWrapper() {
    delete dPtr;
}

float OutputVectorsPropertiesWrapper::getFrequency() const {
    return dPtr->_ovp->Frequency;
}

Optimization OutputVectorsPropertiesWrapper::getOptimization() const {
    Optimization opt;
    ipgml::Optimization o = this->dPtr->_ovp->Opt;
    switch (o) {
    case ipgml::Optimization::Default: opt = Optimization::DEFAULT; break;
    case ipgml::Optimization::Quality: opt = Optimization::QUALITY; break;
    case ipgml::Optimization::Speed: opt = Optimization::SPEED; break;
    }
    return opt;
}

float OutputVectorsPropertiesWrapper::getPitch() const {
    return dPtr->_ovp->Pitch;
}

float OutputVectorsPropertiesWrapper::getPulseEnergy() const {
    return dPtr->_ovp->PulseEnergy;
}

float OutputVectorsPropertiesWrapper::getPulseWidth() const {
    return dPtr->_ovp->PulseWidth;
}
