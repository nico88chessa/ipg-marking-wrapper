#using "ipg/IpgMarkingGraphicsLibrary.dll"

#include "stdafx.h"
#include <msclr/auto_gcroot.h>

#include "Scanner.h"
#include "Point.h"

using namespace System;
using namespace System::Runtime::InteropServices;
namespace ipgml = IpgMarkingGraphicsLibrary;

using namespace ipg_marking_library_wrapper;

class ipg_marking_library_wrapper::ScannerPrivate {
public:
    msclr::auto_gcroot<ipgml::Scanner^> _s;
    GCHandle handle;

public:
    ScannerPrivate(System::String^ name, bool lock, IpgMarkingGraphicsLibrary::Units unit) {
        _s = gcnew ipgml::Scanner(name, lock, unit);
    }

    ~ScannerPrivate() {
        unlock();
    }

    void* getManaged() {
        if (!handle.IsAllocated)
            handle = GCHandle::Alloc(_s.get());
        void* obj = GCHandle::ToIntPtr(handle).ToPointer();
        return obj;
    }

    void unlock() {
        if (handle.IsAllocated)
            handle.Free();
    }

};


Scanner::Scanner(const std::string& name, bool lock, Units u, std::string& err) : dPtr(nullptr) {

    isToCloseBeforeDelete = lock ? true : false;

    System::String^ _name = gcnew System::String(name.c_str());
    //std::string prova = "laser-5410ECA7BC1A.local";

    ipgml::Units _u;
    bool res = false;
    switch (u) {
    case Units::INCHES: _u = ipgml::Units::Inches; break;
    case Units::METERS: _u = ipgml::Units::Meters; break;
    case Units::MICRONS: _u = ipgml::Units::Microns; break;
    case Units::MILLIMETERS: _u = ipgml::Units::Millimeters; break;
    }

    try {
        dPtr = new ScannerPrivate(_name, lock, _u);
    }
    catch (System::Exception^ e) {
        const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(e->Message)).ToPointer();
        err = chars;
        Marshal::FreeHGlobal(IntPtr((void*)chars));
    }

}

Scanner::~Scanner() {

    if (isToCloseBeforeDelete)
        this->close();

    delete dPtr;
}

void* Scanner::getManagedObject() {
    if (dPtr == nullptr)
        return nullptr;

    void* obj = dPtr->getManaged();
    return obj;
}

void Scanner::releaseManagedObject() { 
    dPtr->unlock();
}

void Scanner::close() {
    if (dPtr == nullptr)
        return;

    try {
        dPtr->_s->Close();
        isToCloseBeforeDelete = false;
    }
    catch (System::Exception^ e) {
        const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(e->Message)).ToPointer();
        Marshal::FreeHGlobal(IntPtr((void*)chars));
    }
}

void Scanner::config(OutputPointsProperties& properties, float pitch) {
    if (dPtr == nullptr)
        return;
    GCHandle handle = GCHandle::FromIntPtr(IntPtr(properties.getManagedPtr()));
    ipgml::OutputPointsProperties^ obj = (ipgml::OutputPointsProperties^)handle.Target;
    dPtr->_s->Config(obj, pitch);
    properties.releaseManagedPtr();
}

void Scanner::config(OutputVectorsProperties opp) {
}

void Scanner::exit() {
    if (dPtr == nullptr)
        return;

    dPtr->_s->Exit();
}

void Scanner::finalize() {
}

bool Scanner::isDone() {
    if (dPtr == nullptr)
        return true;

    return dPtr->_s->IsDone();
}

bool Scanner::isWaitingEvent() {
    if (dPtr == nullptr)
        return false;

    return dPtr->_s->IsWaitingEvent();
}

void Scanner::lock() {
    if (dPtr == nullptr)
        return;

    dPtr->_s->Lock();
}

void Scanner::output(PointList& list) {

    GCHandle handle = GCHandle::FromIntPtr(IntPtr(list.getManagedPtr()));
    ipgml::PointList^ obj = (ipgml::PointList^)handle.Target;
    dPtr->_s->Output(obj);
    list.releaseManagedPtr();

}

void Scanner::output(PointList& list, OutputPointsProperties& properties) {

    GCHandle handleList = GCHandle::FromIntPtr(IntPtr(list.getManagedPtr()));
    GCHandle handleProp = GCHandle::FromIntPtr(IntPtr(properties.getManagedPtr()));
    ipgml::PointList^ l = (ipgml::PointList^)handleList.Target;
    ipgml::OutputPointsProperties^ p = (ipgml::OutputPointsProperties^)handleProp.Target;
    dPtr->_s->Output(l, p);
    list.releaseManagedPtr();
    properties.releaseManagedPtr();

}

std::vector<ScannerInfo> Scanner::scanners() {
    
    auto scannerList = ipgml::Scanner::Scanners();
    std::vector<ScannerInfo> list;
    
    for (int i = 0; i < scannerList->Count; ++i) {

        ipgml::ScannerInfo^ p = scannerList->ToArray()[i];

        ConnectionStatus c;
        std::string name;

        switch (p->ConnectionStatus) {
        case ipgml::ConnectionStatus::Available: c = ConnectionStatus::AVAILABLE; break;
        case ipgml::ConnectionStatus::Busy: ConnectionStatus::BUSY; break;
        }
        const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(p->name)).ToPointer();
        name = chars;
        Marshal::FreeHGlobal(IntPtr((void*)chars));

        list.push_back(ScannerInfo(c, name));

    }

    return list;

}

void Scanner::unlock() {
    if (dPtr == nullptr)
        return;

    dPtr->_s->Unlock();
}

void Scanner::wait(float seconds) {
    if (dPtr == nullptr)
        return;

    dPtr->_s->Wait(seconds);
}

void Scanner::wait(WaitEvent we) {
    if (dPtr == nullptr)
        return;

    ipgml::WaitEvent _ev;
    switch (we) {
    case WaitEvent::GPI0: _ev = ipgml::WaitEvent::GPI0; break;
    case WaitEvent::GPI1: _ev = ipgml::WaitEvent::GPI1; break;
    case WaitEvent::GPI2: _ev = ipgml::WaitEvent::GPI2; break;
    case WaitEvent::GPI3: _ev = ipgml::WaitEvent::GPI3; break;
    case WaitEvent::StartBit: _ev = ipgml::WaitEvent::StartBit; break;
    }

    dPtr->_s->Wait(_ev);

}

void Scanner::clearLaserEntry() {
    dPtr->_s->PointParameters->ClearLaserEntries();
}

void Scanner::addLaserEntry(float dwell, float width, float powerPercent, int count) {
    dPtr->_s->PointParameters->AddLaserEntry(dwell, width, powerPercent, count);
}

void Scanner::laser(LaserAction l) {

    ipgml::LaserAction _action;
    switch (l) {
        case LaserAction::Disable: _action = ipgml::LaserAction::Disable; break;
        case LaserAction::Enable: _action = ipgml::LaserAction::Enable; break;
    }
    dPtr->_s->Laser(_action);

}

void Scanner::guide(bool guideValue) {
    dPtr->_s->Guide = guideValue;
}
