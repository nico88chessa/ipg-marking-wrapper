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
    /*msclr::auto_gcroot<ipgml::PolygonProperties^> _pp;
    GCHandle handle;*/
    POLYGONPROPERTIES_HANDLER handler;

public:
    PolygonPropertiesPrivate(int numberOfSides, float radius) {
        //_pp = gcnew ipgml::PolygonProperties(numberOfSides, radius);
        handler = GCHandle::ToIntPtr(GCHandle::Alloc(
            gcnew ipgml::PolygonProperties(numberOfSides, radius))).ToPointer();
    }

    ~PolygonPropertiesPrivate() {
        //unlock();
        GCHandle h = GCHandle::FromIntPtr(IntPtr(handler));
        /*if (h.Equals(test)) {
        std::cout << "Yeah sono uguali";
        }*/
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

    /*void* getManaged() {
        if (!handle.IsAllocated)
            handle = GCHandle::Alloc(_pp.get());
        void* obj = GCHandle::ToIntPtr(handle).ToPointer();
        return obj;
    }

    void unlock() {
        if (handle.IsAllocated)
            handle.Free();
    }*/

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

//void* PolygonProperties::getManagedPtr() {
//    if (dPtr == nullptr)
//        return nullptr;
//
//    void* obj = dPtr->getManaged();
//    return obj;
//}
//
//void PolygonProperties::releaseManagedPtr() {
//    dPtr->unlock();
//}

std::ostream& ipg_marking_library_wrapper::operator<<(std::ostream& os, const PolygonProperties& obj) {
    return os << "PolygonProperties - N.sides: " << obj.getNumberOfSides() << "; radius: " << obj.getRadius();
}
