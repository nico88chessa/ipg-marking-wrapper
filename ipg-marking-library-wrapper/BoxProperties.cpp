#using "ipg/IpgMarkingGraphicsLibrary.dll"

#include "stdafx.h"
#include <msclr/auto_gcroot.h>

#include "BoxProperties.h"

using namespace System;
using namespace System::Runtime::InteropServices;
namespace ipgml = IpgMarkingGraphicsLibrary;

using namespace ipg_marking_library_wrapper;


class ipg_marking_library_wrapper::BoxPropertiesPrivate {
public:
    BOXPROPERTIES_HANDLER handler;

public:
    BoxPropertiesPrivate(float size) {
        handler = GCHandle::ToIntPtr(
            GCHandle::Alloc(gcnew ipgml::BoxProperties(size))).ToPointer();
    }

    BoxPropertiesPrivate(float width, float height) {
        handler = GCHandle::ToIntPtr(
            GCHandle::Alloc(gcnew ipgml::BoxProperties(width, height))).ToPointer();
    }

    BoxPropertiesPrivate(float width, float height, float radius) {
        handler = GCHandle::ToIntPtr(
            GCHandle::Alloc(gcnew ipgml::BoxProperties(width, height, radius))).ToPointer();
    }

    BoxPropertiesPrivate(float width, float height, float radius, float segmentsPerCorner) {
        handler = GCHandle::ToIntPtr(
            GCHandle::Alloc(gcnew ipgml::BoxProperties(width, height, radius, segmentsPerCorner))).ToPointer();
    }

    ~BoxPropertiesPrivate() {
        GCHandle h = GCHandle::FromIntPtr(IntPtr(handler));
        delete GCHandle::FromIntPtr(IntPtr(handler)).Target;
        handler = nullptr;
        h.Free();
    }

    ipgml::BoxProperties^ operator->() const {
        return static_cast<ipgml::BoxProperties^>(GCHandle::FromIntPtr(IntPtr(handler)).Target);
    }

    ipgml::BoxProperties^ get() const {
        return static_cast<ipgml::BoxProperties^>(GCHandle::FromIntPtr(IntPtr(handler)).Target);
    }

};


BoxProperties::BoxProperties(float size) {
    dPtr = new BoxPropertiesPrivate(size);
}

BoxProperties::BoxProperties(float width, float height) {
    dPtr = new BoxPropertiesPrivate(width, height);
}

BoxProperties::BoxProperties(float width, float height, float radius) {
    dPtr = new BoxPropertiesPrivate(width, height, radius);
}

BoxProperties::BoxProperties(float width, float height, float radius, float segmentsPerCorner) {
    dPtr = new BoxPropertiesPrivate(width, height, radius, segmentsPerCorner);
}

BoxProperties::~BoxProperties() {
    delete dPtr;
}

float BoxProperties::getHeight() const {
    if (dPtr == nullptr)
        return 0.0f;
    return (*dPtr)->Height;
}

float BoxProperties::getWidth() const {
    if (dPtr == nullptr)
        return 0.0f;
    return (*dPtr)->Width;
}

float BoxProperties::getRadius() const {
    if (dPtr == nullptr)
        return 0.0f;
    return (*dPtr)->Radius;
}

float BoxProperties::getSegments() const {
    if (dPtr == nullptr)
        return 0.0f;
    return (*dPtr)->Segments;
}

CONST_BOXPROPERTIES_HANDLER BoxProperties::getManagedPtr() const {
    if (dPtr == nullptr)
        return nullptr;

    return dPtr->handler;
}

std::ostream& ipg_marking_library_wrapper::operator<<(std::ostream& os, const BoxProperties& obj) {
    return os << "PolygonProperties: " \
        << "width: " << obj.getWidth() \
        << "height: " << obj.getHeight() \
        << "radius: " << obj.getRadius() \
        << "segments: " << obj.getSegments();
}
