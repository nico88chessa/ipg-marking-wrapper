//#using "ipg/IpgMarkingGraphicsLibrary.dll"

#include "stdafx.h"
//#include <msclr/auto_gcroot.h>

#include "ScannerInfo.h"

using namespace System;
using namespace System::Runtime::InteropServices;
//namespace ipgml = IpgMarkingGraphicsLibrary;

using namespace ipg_marking_library_wrapper;

//class ipg_marking_library_wrapper::ScannerInfoWPrivate {
//public:
//    msclr::auto_gcroot<ipgml::ScannerInfo> _scannerInfo;
//    GCHandle handle;
//
//public:
//    ScannerInfoWPrivate() {
//        handle = GCHandle::Alloc(_scannerInfo);
//    }
//    ~ScannerInfoWPrivate() {
//        handle.Free();
//    }
//};

ScannerInfo::ScannerInfo(ConnectionStatus status, const std::string& name) :
    status(status), name(name) {
    /*this->dPtr = new ScannerInfoWPrivate();

    ipgml::ConnectionStatus cs;
    switch (status) {
    case ConnectionStatus::AVAILABLE: cs = ipgml::ConnectionStatus::Available; break;
    case ConnectionStatus::BUSY: cs = ipgml::ConnectionStatus::Busy; break;
    }

    dPtr->_scannerInfo = gcnew ipgml::ScannerInfo();*/
}

ScannerInfo::~ScannerInfo() {
    //delete dPtr;
}

ConnectionStatus ScannerInfo::getStatus() const {
    return status;
}

std::string ScannerInfo::getName() const {
    return name;
}
