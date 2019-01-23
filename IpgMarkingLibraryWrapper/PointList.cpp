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
    msclr::gcroot<ipgml::PointList^> _pl;
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
    }
};

PointList::PointList() {
    dPtr = new PointListPrivate();
}

PointList::PointList(std::list<Point>& points) {
    
    auto list = gcnew System::Collections::Generic::List<ipgml::Point^>();

    while (!points.empty()) {
        Point& p = points.front();
        Point c = p;// std::move(p);
        points.pop_front();
        int x = c.getX();
        int y = c.getY();
        GCHandle^ handle = GCHandle::FromIntPtr(IntPtr(c.getManagedObject()));
        ipgml::Point^ point = (ipgml::Point^)handle->Target;
        c.releaseManagedObject();
        
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
    Point point(GCHandle::ToIntPtr(handle).ToPointer());
    handle.Free();

    return point;
}

void PointList::shift(float x, float y, float z) {
    if (this->dPtr == nullptr)
        return;
    this->dPtr->_pl->Shift(x, y, z);
}
