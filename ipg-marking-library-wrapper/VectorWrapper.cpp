#using "ipg/IpgMarkingGraphicsLibrary.dll"

#include "stdafx.h"
#include <msclr/gcroot.h>

#include "VectorWrapper.h"
#include "Vector.h"

using namespace System;
using namespace System::Runtime::InteropServices;
namespace ipgml = IpgMarkingGraphicsLibrary;

using namespace ipg_marking_library_wrapper;


class ipg_marking_library_wrapper::VectorWrapperPrivate {
public:
    msclr::gcroot<ipgml::Vector^> _v;
};


VectorWrapper::VectorWrapper(VECTORWRAPPER_HANDLE_PTR ptr) : dPtr(nullptr) {

    if (ptr == nullptr)
        return;
    this->dPtr = new VectorWrapperPrivate();
    IntPtr pointer(ptr);
    GCHandle handle = GCHandle::FromIntPtr(pointer);
    ipgml::Vector^ obj = (ipgml::Vector^) handle.Target;
    //this->dPtr->_p = gcnew ipgml::Point();// obj;// gcnew ipgml::Point(obj);
    //this->dPtr->_p.reset(obj);
    this->dPtr->_v = obj;

}

VectorWrapper::VectorWrapper(VectorWrapper&& other) {
    this->dPtr = other.dPtr;
    other.dPtr = nullptr;
}

VectorWrapper::~VectorWrapper() {
    delete dPtr;
}

VectorWrapper& VectorWrapper::operator=(VectorWrapper&& other) {
    if (&other == this)
        return *this;
    delete dPtr;
    this->dPtr = other.dPtr;
    other.dPtr = nullptr;
    return *this;
}

Vector VectorWrapper::clone() {
    GCHandle handle = GCHandle::Alloc(dPtr->_v);
    VECTORWRAPPER_HANDLE_PTR ptr = GCHandle::ToIntPtr(handle).ToPointer();
    Vector clonedVet(ptr);
    handle.Free();
    return clonedVet;
}

float VectorWrapper::getLength() const {
    if (dPtr == nullptr)
        return 0.0f;

    return dPtr->_v->Length;
}

PointWrapper VectorWrapper::getStart() const {
    if (dPtr == nullptr)
        return PointWrapper();

    ipgml::Point^ p = dPtr->_v->Start;
    GCHandle handle = GCHandle::Alloc(p);
    PointWrapper res(GCHandle::ToIntPtr(handle).ToPointer());
    handle.Free();
    return res;
}

void VectorWrapper::setStart(const Point& start) {
    GCHandle hStartPoint = GCHandle::FromIntPtr(IntPtr(const_cast<POINT_HANDLER>(start.getManagedPtr())));
    ipgml::Point^ startManaged = (ipgml::Point^) hStartPoint.Target;
    dPtr->_v->Start = startManaged;
}

PointWrapper VectorWrapper::getEnd() const {
    if (dPtr == nullptr)
        return PointWrapper();

    ipgml::Point^ p = dPtr->_v->End;
    GCHandle handle = GCHandle::Alloc(p);
    PointWrapper res(GCHandle::ToIntPtr(handle).ToPointer());
    handle.Free();
    return res;
}

void VectorWrapper::setEnd(const Point& end) {
    GCHandle hEndPoint = GCHandle::FromIntPtr(IntPtr(const_cast<POINT_HANDLER>(end.getManagedPtr())));
    ipgml::Point^ endManaged = (ipgml::Point^) hEndPoint.Target;
    dPtr->_v->Start = endManaged;
}

std::ostream& ipg_marking_library_wrapper::operator<<(std::ostream& os, const VectorWrapper& obj) {
    PointWrapper start = obj.getStart();
    PointWrapper end = obj.getEnd();
    /*return os << "Vector Start (" << start.getX() << "; " << start.getY() << ") - " << \
    "End (" << end.getX() << "; " << end.getY() << ")" << std::endl;*/
    return os << "VectorWrapper: Start " << start << " - End " << end;
}
