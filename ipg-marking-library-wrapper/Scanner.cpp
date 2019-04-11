#using "ipg/IpgMarkingGraphicsLibrary.dll"

#include "stdafx.h"
#include <msclr/auto_gcroot.h>
#include <msclr/marshal_cppstd.h>

#include "Scanner.h"
#include "Point.h"
#include "LibraryException.h"

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
    
    } catch (ipgml::LibraryException^ e) {
        
        System::String^ managedMessage = e->Message;
        msclr::interop::marshal_context context;
        std::string message = context.marshal_as<std::string>(managedMessage);
        throw LibraryException(message);

    }

}

Scanner::~Scanner() {

    if (isToCloseBeforeDelete)
        this->close();

    delete dPtr;
}

void* Scanner::getManagedPtr() {
    if (dPtr == nullptr)
        return nullptr;

    void* obj = dPtr->getManaged();
    return obj;
}

void Scanner::releaseManagedPtr() { 
    dPtr->unlock();
}

void Scanner::close() {
    if (dPtr == nullptr)
        return;

    try {
        dPtr->_s->Close();
        isToCloseBeforeDelete = false;
    } catch (ipgml::LibraryException^ e) {

        System::String^ managedMessage = e->Message;
        msclr::interop::marshal_context context;
        std::string message = context.marshal_as<std::string>(managedMessage);
        throw LibraryException(message);

    }

}

void Scanner::config(OutputPointsProperties& properties, float pitch) {
    if (dPtr == nullptr)
        return;
    GCHandle handle = GCHandle::FromIntPtr(IntPtr(properties.getManagedPtr()));
    ipgml::OutputPointsProperties^ obj = (ipgml::OutputPointsProperties^)handle.Target;
    
    try {
        dPtr->_s->Config(obj, pitch);
    } catch (ipgml::LibraryException^ e) {

        properties.releaseManagedPtr();
        System::String^ managedMessage = e->Message;
        msclr::interop::marshal_context context;
        std::string message = context.marshal_as<std::string>(managedMessage);
        throw LibraryException(message);

    }
    
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
    
    try {
        dPtr->_s->Output(obj);
    } catch (ipgml::LibraryException^ e) {

        list.releaseManagedPtr();
        System::String^ managedMessage = e->Message;
        msclr::interop::marshal_context context;
        std::string message = context.marshal_as<std::string>(managedMessage);
        throw LibraryException(message);

    }
    
    list.releaseManagedPtr();

}

void Scanner::output(PointList& list, OutputPointsProperties& properties) {

    GCHandle handleList = GCHandle::FromIntPtr(IntPtr(list.getManagedPtr()));
    GCHandle handleProp = GCHandle::FromIntPtr(IntPtr(properties.getManagedPtr()));
    ipgml::PointList^ l = (ipgml::PointList^)handleList.Target;
    ipgml::OutputPointsProperties^ p = (ipgml::OutputPointsProperties^)handleProp.Target;
    
    try {
        dPtr->_s->Output(l, p);
        list.releaseManagedPtr();
    } catch (ipgml::LibraryException^ e) {

        list.releaseManagedPtr();
        properties.releaseManagedPtr();
        System::String^ managedMessage = e->Message;
        msclr::interop::marshal_context context;
        std::string message = context.marshal_as<std::string>(managedMessage);
        throw LibraryException(message);

    }
    properties.releaseManagedPtr();

}

void Scanner::output(VectorList & list) {

    GCHandle handle = GCHandle::FromIntPtr(IntPtr(list.getManagedPtr()));
    ipgml::VectorList^ obj = (ipgml::VectorList^) handle.Target;

    try {
        dPtr->_s->Output(obj);
        list.releaseManagedPtr();
    
    } catch (ipgml::LibraryException^ e) {

        list.releaseManagedPtr();
        System::String^ managedMessage = e->Message;
        msclr::interop::marshal_context context;
        std::string message = context.marshal_as<std::string>(managedMessage);
        throw LibraryException(message);
    
    }

}

void Scanner::output(VectorList & list, OutputVectorsProperties& properties) {

    GCHandle handleList = GCHandle::FromIntPtr(IntPtr(list.getManagedPtr()));
    GCHandle handleProp = GCHandle::FromIntPtr(IntPtr(properties.getManagedPtr()));
    ipgml::VectorList^ vl = (ipgml::VectorList^) handleList.Target;
    ipgml::OutputVectorsProperties^ p = (ipgml::OutputVectorsProperties^)handleProp.Target;

    try {
        dPtr->_s->Output(vl, p);
        list.releaseManagedPtr();
    }
    catch (ipgml::LibraryException^ e) {

        list.releaseManagedPtr();
        properties.releaseManagedPtr();
        System::String^ managedMessage = e->Message;
        msclr::interop::marshal_context context;
        std::string message = context.marshal_as<std::string>(managedMessage);
        throw LibraryException(message);

    }

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

    try {
        dPtr->_s->Unlock();
    } catch (ipgml::LibraryException^ e) {

        System::String^ managedMessage = e->Message;
        msclr::interop::marshal_context context;
        std::string message = context.marshal_as<std::string>(managedMessage);
        throw LibraryException(message);

    }

}

void Scanner::wait(float seconds) {
    if (dPtr == nullptr)
        return;

    try {
        dPtr->_s->Wait(seconds);
    } catch (ipgml::LibraryException^ e) {

        System::String^ managedMessage = e->Message;
        msclr::interop::marshal_context context;
        std::string message = context.marshal_as<std::string>(managedMessage);
        throw LibraryException(message);

    }

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

    try {
        dPtr->_s->Wait(_ev);
    } catch (ipgml::LibraryException^ e) {

        System::String^ managedMessage = e->Message;
        msclr::interop::marshal_context context;
        std::string message = context.marshal_as<std::string>(managedMessage);
        throw LibraryException(message);

    }

}

void Scanner::ppClearLaserEntry() {
    dPtr->_s->PointParameters->ClearLaserEntries();
}

void Scanner::ppAddLaserEntry(float dwell, float width, float powerPercent, int count) {

    try {
        dPtr->_s->PointParameters->AddLaserEntry(dwell, width, powerPercent, count);
    } catch (ipgml::LibraryException^ e) {

        System::String^ managedMessage = e->Message;
        msclr::interop::marshal_context context;
        std::string message = context.marshal_as<std::string>(managedMessage);
        throw LibraryException(message);

    }

}

void Scanner::vpClearLaserEntry() {
    if (dPtr == nullptr)
        return;

    try {
        dPtr->_s->VectorParameters->ClearLaserEntries();
    } catch (ipgml::LibraryException^ e) {

        System::String^ managedMessage = e->Message;
        msclr::interop::marshal_context context;
        std::string message = context.marshal_as<std::string>(managedMessage);
        throw LibraryException(message);

    }

}

void Scanner::vpAddLaserEntry(float velocity, float frequency, float pulseWidth, float powerPercent) {

    if (dPtr == nullptr)
        return;

    try {
        dPtr->_s->VectorParameters->AddLaserEntry(velocity, frequency, pulseWidth, powerPercent);
    } catch (ipgml::LibraryException^ e) {

        System::String^ managedMessage = e->Message;
        msclr::interop::marshal_context context;
        std::string message = context.marshal_as<std::string>(managedMessage);
        throw LibraryException(message);

    }

}

void Scanner::park(const Point& p) {

    if (dPtr == nullptr)
        return;
    
    ipgml::Point^ parkPoint = gcnew ipgml::Point(p.getX(), p.getY(), p.getZ());

    try {
        dPtr->_s->Park(parkPoint);
    } catch (ipgml::LibraryException^ e) {

        System::String^ managedMessage = e->Message;
        msclr::interop::marshal_context context;
        std::string message = context.marshal_as<std::string>(managedMessage);
        throw LibraryException(message);

    }
     
}

void Scanner::laser(LaserAction l) {

    ipgml::LaserAction _action;
    switch (l) {
        case LaserAction::Disable: _action = ipgml::LaserAction::Disable; break;
        case LaserAction::Enable: _action = ipgml::LaserAction::Enable; break;
    }

    try {
        dPtr->_s->Laser(_action);
    } catch (ipgml::LibraryException^ e) {

        System::String^ managedMessage = e->Message;
        msclr::interop::marshal_context context;
        std::string message = context.marshal_as<std::string>(managedMessage);
        throw LibraryException(message);

    }

}

void Scanner::guide(bool guideValue) {
    dPtr->_s->Guide = guideValue;
}
