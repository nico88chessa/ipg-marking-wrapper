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
    msclr::auto_gcroot<ipgml::Scanner^> _scanner;
    GCHandle handle;

public:
    ScannerPrivate(System::String^ name, bool lock, IpgMarkingGraphicsLibrary::Units unit) {
        _scanner = gcnew ipgml::Scanner(name, lock, unit);
        handle = GCHandle::Alloc(_scanner);
    }
    ~ScannerPrivate() {
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

}

Scanner::~Scanner() {

    if (isToCloseBeforeDelete)
        this->close();

    delete dPtr;
}

void* Scanner::getManagedObject() {
    if (dPtr == nullptr)
        return nullptr;
    
    return GCHandle::ToIntPtr(dPtr->handle).ToPointer();
    
}

void Scanner::close() {
    if (dPtr == nullptr)
        return;

    try {
        dPtr->_scanner->Close();
    }
    catch (System::Exception^ e) {
        const char* chars = (const char*)(Marshal::StringToHGlobalAnsi(e->Message)).ToPointer();
        Marshal::FreeHGlobal(IntPtr((void*)chars));
    }
}

void Scanner::config(OutputPointsProperties properties, float pitch) {
    if (dPtr == nullptr)
        return;

    
}

void Scanner::config(OutputVectorsProperties opp) {
}

void Scanner::exit() {
    if (dPtr == nullptr)
        return;

    dPtr->_scanner->Exit();
}

void Scanner::finalize() {
}

bool Scanner::isDone() {
    if (dPtr == nullptr)
        return true;

    return dPtr->_scanner->IsDone();
}

bool Scanner::isWaitingEvent() {
    if (dPtr == nullptr)
        return false;

    return dPtr->_scanner->IsWaitingEvent();
}

void Scanner::lock() {
    if (dPtr == nullptr)
        return;

    dPtr->_scanner->Lock();
}

//void Scanner::output(PointList ^) {
//}
//
//void Scanner::output(PointList ^, OutputPointsProperties ^) {
//}
//
//void Scanner::output(VectorList ^) {
//}
//
//void Scanner::output(VectorList ^, OutputVectorsProperties ^) {
//}

std::vector<ScannerInfo> Scanner::scanners() {
    /*if (dPtr == nullptr)
        return std::vector<ScannerInfo>();*/

    /*auto test = dPtr->_scanner->Scanners();
    Collections::Generic::List<ipgml::ScannerInfo>^ scannerList = dPtr->_scanner->Scanners();*/
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

    dPtr->_scanner->Unlock();
}

void Scanner::wait(float seconds) {
    if (dPtr == nullptr)
        return;

    dPtr->_scanner->Wait(seconds);
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

    dPtr->_scanner->Wait(_ev);

}

PointParameters Scanner::getPointParameters() {
    
    ipgml::PointParameters^ pp = dPtr->_scanner->PointParameters;
    GCHandle handle = GCHandle::Alloc(pp);
    IntPtr pointer = GCHandle::ToIntPtr(handle);
    void* ptr = pointer.ToPointer();

    //PointParameters* temp = new PointParameters(ptr);
    PointParameters temp(ptr);
    handle.Free();
    //return std::move(temp);
    return temp;
}
        
