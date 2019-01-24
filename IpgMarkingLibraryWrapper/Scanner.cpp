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

class ipg_marking_library_wrapper::PointParametersHandler {
public:
    GCHandle handle;

    PointParametersHandler() { }

    ~PointParametersHandler() {
        if (handle.IsAllocated)
            handle.Free();
    }
};


Scanner::Scanner(const std::string& name, bool lock, Units u, std::string& err) : dPtr(nullptr) {

    isToCloseBeforeDelete = lock ? true : false;

    System::String^ _name = gcnew System::String(name.c_str());
    //std::string prova = "laser-5410ECA7BC1A.local";
    //System::Boolean^ v = gcnew System::Boolean(false);
    //ipgml::Units^ c = gcnew ipgml::Units^(ipgml::Units::Millimeters);

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
    ppHandler = new PointParametersHandler();

}

Scanner::~Scanner() {

    if (isToCloseBeforeDelete)
        this->close();

    delete dPtr;
    delete ppHandler;
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

std::vector<ScannerInfo> Scanner::scanners() {
    /*if (dPtr == nullptr)
        return std::vector<ScannerInfo>();*/

        /*auto test = dPtr->_s->Scanners();
        Collections::Generic::List<ipgml::ScannerInfo>^ scannerList = dPtr->_s->Scanners();*/
    auto scannerList = ipgml::Scanner::Scanners();
    std::vector<ScannerInfo> list;
    //ipgml::ScannerInfo^ p = gcnew ipgml::ScannerInfo();

    for (int i = 0; i < scannerList->Count; ++i) {

        //p = scannerList->ToArray()[i];
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

PointParametersWrapper Scanner::getManagedPointParameters() {

    ipgml::PointParameters^ pp = dPtr->_s->PointParameters;
    ppHandler->handle = GCHandle::Alloc(pp);
    IntPtr pointer = GCHandle::ToIntPtr(ppHandler->handle);
    PointParametersWrapper temp(pointer.ToPointer());
    return temp;

}

void Scanner::releaseManagedPointParameters() {
    if (ppHandler->handle.IsAllocated)
        ppHandler->handle.Free();

}
        
