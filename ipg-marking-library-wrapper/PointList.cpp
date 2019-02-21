#using "ipg/IpgMarkingGraphicsLibrary.dll"

#include "stdafx.h"
#include <msclr/auto_gcroot.h>

#include "PointList.h"


using namespace System;
using namespace System::Runtime::InteropServices;
namespace ipgml = IpgMarkingGraphicsLibrary;

using namespace ipg_marking_library_wrapper;

class ipg_marking_library_wrapper::PointListPrivate {
public:
    msclr::auto_gcroot<ipgml::PointList^> _pl;
    GCHandle handle;

public:
    PointListPrivate(System::Collections::Generic::List<ipgml::Point^>^ list) {
        _pl = gcnew ipgml::PointList(list);
    }

    PointListPrivate() {
        _pl = gcnew ipgml::PointList();
    }

    PointListPrivate(ipgml::PointList^ other) {
        _pl = other;
    }

    ~PointListPrivate() {
        unlock();
    }

    void* getManaged() {
        if (!handle.IsAllocated)
            handle = GCHandle::Alloc(_pl.get());
        IntPtr t(GCHandle::ToIntPtr(handle));
        void* obj = t.ToPointer();
        return obj;
    }

    void unlock() {
        if (handle.IsAllocated)
            handle.Free();
    }
};

PointList::PointList() {
    dPtr = new PointListPrivate();
}

PointList::PointList(std::list<Point>& points) {
    
    auto list = gcnew System::Collections::Generic::List<ipgml::Point^>();

    while (!points.empty()) {
        //Point& p = points.front();
        Point c = points.front();
        points.pop_front();
        int x = c.getX();
        int y = c.getY();
        GCHandle^ handle = GCHandle::FromIntPtr(IntPtr(c.getManagedPtr()));
        ipgml::Point^ point = (ipgml::Point^)handle->Target;
        c.releaseManagedPtr();
        
        list->Add(point);
    }

    dPtr = new PointListPrivate(list);
}

PointList::PointList(PointList && other) {
    this->dPtr = other.dPtr;
    other.dPtr = nullptr;
}


PointList::~PointList() {
    if (dPtr != nullptr)
        delete dPtr;
}

int PointList::count() const {
    return this->dPtr->_pl->Count;
}

Point PointList::element(int i) {

    ipgml::Point^ p = dPtr->_pl->Element(i);
    GCHandle handle = GCHandle::Alloc(p);
    Point res(GCHandle::ToIntPtr(handle).ToPointer());
    handle.Free();
    return res;
}

void PointList::shift(float x, float y, float z) {
    if (this->dPtr == nullptr)
        return;
    this->dPtr->_pl->Shift(x, y, z);
}

void PointList::rotate(double z) {
    if (this->dPtr == nullptr)
        return;
    this->dPtr->_pl->Rotate(z);
}

void PointList::rotate(double x, double y, double z) {
    if (this->dPtr == nullptr)
        return;
    this->dPtr->_pl->Rotate(x, y, z);
}

void PointList::rotate(float z) {
    if (this->dPtr == nullptr)
        return;
    dPtr->_pl->Rotate(z);
}

void PointList::rotate(float x, float y, float z) {
    if (this->dPtr == nullptr)
        return;
    this->dPtr->_pl->Rotate(x, y, z);
}

void* PointList::getManagedPtr() {
    if (dPtr == nullptr)
        return nullptr;

    void* obj = dPtr->getManaged();
    return obj;
}

void PointList::releaseManagedPtr() {
    dPtr->unlock();
}
