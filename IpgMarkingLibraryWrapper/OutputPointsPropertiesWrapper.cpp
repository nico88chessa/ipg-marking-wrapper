#using "ipg/IpgMarkingGraphicsLibrary.dll"

#include "stdafx.h"
#include <msclr/gcroot.h>

#include "OutputPointsPropertiesWrapper.h"

using namespace System;
using namespace System::Runtime::InteropServices;
namespace ipgml = IpgMarkingGraphicsLibrary;

using namespace ipg_marking_library_wrapper;

class ipg_marking_library_wrapper::OutputPointsPropertiesWrapperPrivate {
public:
    msclr::gcroot<ipgml::OutputPointsProperties^> _opp;
};

OutputPointsPropertiesWrapper::OutputPointsPropertiesWrapper(void* ptr) {
    
    IntPtr pointer(ptr);
    GCHandle handle = GCHandle::FromIntPtr(pointer);
    ipgml::OutputPointsProperties^ obj = (ipgml::OutputPointsProperties^)handle.Target;
    this->dPtr = new OutputPointsPropertiesWrapperPrivate();
    this->dPtr->_opp = obj;

}

OutputPointsPropertiesWrapper::~OutputPointsPropertiesWrapper() {
    delete dPtr;
}

Optimization OutputPointsPropertiesWrapper::getOptimization() const {

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

float OutputPointsPropertiesWrapper::getPulseEnergy() const {
    if (dPtr == nullptr)
        return 0.0f;

    return dPtr->_opp->PulseEnergy;
}
