#using "ipg/IpgMarkingGraphicsLibrary.dll"

#include "stdafx.h"
#include <msclr/auto_gcroot.h>

#include "PolygonProperties.h"

using namespace System;
using namespace System::Runtime::InteropServices;
namespace ipgml = IpgMarkingGraphicsLibrary;

using namespace ipg_marking_library_wrapper;


class ipg_marking_library_wrapper::PolygonPropertiesPrivate {
public:
    POLYGONPROPERTIES_HANDLER handler;

public:
    PolygonPropertiesPrivate(int numberOfSides, float radius) {
        handler = GCHandle::ToIntPtr(GCHandle::Alloc(
            gcnew ipgml::PolygonProperties(numberOfSides, radius))).ToPointer();
    }

    ~PolygonPropertiesPrivate() {
        GCHandle h = GCHandle::FromIntPtr(IntPtr(handler));
        delete GCHandle::FromIntPtr(IntPtr(handler)).Target;
        handler = nullptr;
        h.Free();
    }

    ipgml::PolygonProperties^ operator->() const {
        return static_cast<ipgml::PolygonProperties^>(GCHandle::FromIntPtr(IntPtr(handler)).Target);
    }

    ipgml::PolygonProperties^ get() const {
        return static_cast<ipgml::PolygonProperties^>(GCHandle::FromIntPtr(IntPtr(handler)).Target);
    }

};


PolygonProperties::PolygonProperties(int numberOfSides, float radius) {
    dPtr = new PolygonPropertiesPrivate(numberOfSides, radius);
}

PolygonProperties::~PolygonProperties() {
    delete dPtr;
}

float PolygonProperties::getNumberOfSides() const {
    if (dPtr == nullptr)
        return 0.0f;
    return (*dPtr)->NumberOfSides;
}

float PolygonProperties::getRadius() const {
    if (dPtr == nullptr)
        return 0.0f;
    return (*dPtr)->Radius;
}

CONST_POLYGONPROPERTIES_HANDLER PolygonProperties::getManagedPtr() const {
    if (dPtr == nullptr)
        return nullptr;

    return dPtr->handler;
}

std::ostream& ipg_marking_library_wrapper::operator<<(std::ostream& os, const PolygonProperties& obj) {
    return os << "PolygonProperties - N.sides: " << obj.getNumberOfSides() << "; radius: " << obj.getRadius();
}
