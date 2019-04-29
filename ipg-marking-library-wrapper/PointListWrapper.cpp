#using "ipg/IpgMarkingGraphicsLibrary.dll"

#include "stdafx.h"
#include <msclr/auto_gcroot.h>
#include <msclr/marshal_cppstd.h>

#include "PointList.h"
#include "LibraryException.h"
#include <msclr/gcroot.h>
#include "PointListWrapper.h"


using namespace System;
using namespace System::Runtime::InteropServices;
namespace ipgml = IpgMarkingGraphicsLibrary;

using namespace ipg_marking_library_wrapper;


class ipg_marking_library_wrapper::PointListWrapperPrivate {
public:
    msclr::gcroot<ipgml::PointList^> _pl;
};


PointListWrapper::PointListWrapper(POINTLIST_WRAPPER_HANDLER_PTR ptr) : dPtr(nullptr) {

    if (ptr == nullptr)
        return;
    this->dPtr = new PointListWrapperPrivate();
    IntPtr pointer(ptr);
    GCHandle handle = GCHandle::FromIntPtr(pointer);
    ipgml::PointList^ obj = (ipgml::PointList^) handle.Target;
    //this->dPtr->_p = gcnew ipgml::Point();// obj;// gcnew ipgml::Point(obj);
    //this->dPtr->_p.reset(obj);
    this->dPtr->_pl = obj;
}

PointListWrapper::PointListWrapper(PointListWrapper && other) {
    this->dPtr = other.dPtr;
    other.dPtr = nullptr;
}

PointListWrapper::~PointListWrapper() {
    delete dPtr;
}

PointListWrapper& PointListWrapper::operator=(PointListWrapper&& other) {
    if (&other == this)
        return *this;
    delete dPtr;
    this->dPtr = other.dPtr;
    other.dPtr = nullptr;
    return *this;
}

void PointListWrapper::append(const PointListWrapper& pl) {
    if (dPtr == nullptr)
        return;
    dPtr->_pl->Append(pl.dPtr->_pl);
}

void PointListWrapper::append(const PointList& pl) {
    if (dPtr == nullptr)
        return;

    //GCHandle^ handle = GCHandle::FromIntPtr(IntPtr(pl.getManagedPtr()));
    //ipgml::PointList^ point = (ipgml::PointList^)handle->Target;
    //list->Add(point);
    //c.releaseManagedPtr();
    //dPtr->_pl->Append(pl.d)

}

int PointListWrapper::count() const {
    if (dPtr == nullptr)
        return 0;
    return dPtr->_pl->Count;
}

PointWrapper PointListWrapper::center() const {

    if (dPtr == nullptr)
        return PointWrapper();

    try {

        ipgml::Point^ p = dPtr->_pl->Center;
        GCHandle handle = GCHandle::Alloc(p);
        PointWrapper res(GCHandle::ToIntPtr(handle).ToPointer());
        handle.Free();
        return res;  // copy elided

    } catch (ipgml::LibraryException^ e) {

        System::String^ managedMessage = e->Message;
        msclr::interop::marshal_context context;
        std::string message = context.marshal_as<std::string>(managedMessage);
        throw LibraryException(message);

    }

    return PointWrapper();
}

PointWrapper PointListWrapper::element(int i) const {

    if (dPtr == nullptr)
        return PointWrapper();

    try {

        ipgml::Point^ p = dPtr->_pl->Element(i);
        GCHandle handle = GCHandle::Alloc(p);
        PointWrapper res(GCHandle::ToIntPtr(handle).ToPointer());
        handle.Free();
        return res;  // copy elided

    } catch (ipgml::LibraryException^ e) {

        System::String^ managedMessage = e->Message;
        msclr::interop::marshal_context context;
        std::string message = context.marshal_as<std::string>(managedMessage);
        throw LibraryException(message);

    }

    return PointWrapper();
}

void PointListWrapper::shift(float x, float y, float z) {
    if (dPtr == nullptr)
        return;
    dPtr->_pl->Shift(x, y, z);
}

void PointListWrapper::rotate(double z) {
    if (dPtr == nullptr)
        return;
    dPtr->_pl->Rotate(z);
}

void PointListWrapper::rotate(double x, double y, double z) {
    if (dPtr == nullptr)
        return;
    dPtr->_pl->Rotate(x, y, z);
}

void PointListWrapper::rotate(float z) {
    if (dPtr == nullptr)
        return;
    dPtr->_pl->Rotate(z);
}

void PointListWrapper::rotate(float x, float y, float z) {
    if (dPtr == nullptr)
        return;
    dPtr->_pl->Rotate(x, y, z);
}

std::ostream& ipg_marking_library_wrapper::operator<<(std::ostream& os, const PointListWrapper& obj) {
    if (obj.dPtr == nullptr)
        return os << "PointListWrapper not initialized";
    int size = obj.count();
    for (int i = 0; i < size; ++i)
        os << obj.element(i) << std::endl;
    return os;
}
