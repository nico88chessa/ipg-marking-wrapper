// Il blocco ifdef seguente viene in genere usato per creare macro che semplificano
// l'esportazione da una DLL. Tutti i file all'interno della DLL sono compilati con il simbolo IPGMARKINGLIBRARYWRAPPER_EXPORTS
// definito nella riga di comando. Questo simbolo non deve essere definito in alcun progetto
// che usa questa DLL. In questo modo qualsiasi altro progetto i cui file di origine includono questo file vedranno le funzioni
// le funzioni di IPGMARKINGLIBRARYWRAPPER_API come se fossero importate da una DLL, mentre questa DLL considera i simboli
// definiti con questa macro come esportati.

#pragma once

#include "IpgmlDef.h"
#include <iostream>
#include <vector>

#include "Enums.h"
#include "ScannerInfo.h"
#include "OutputPointsProperties.h"
#include "OutputVectorsProperties.h"
#include "PointParameters.h"
#include "PointParametersWrapper.h"

namespace ipg_marking_library_wrapper {

    class ScannerPrivate;
    class PointParametersHandler;

    class IPGMARKINGLIBRARYWRAPPER_API Scanner {
    private:
        ScannerPrivate* dPtr;
        PointParametersHandler* ppHandler;

        bool isToCloseBeforeDelete;

    public:
        Scanner(const std::string& name, bool lock, Units u, std::string& err);
        ~Scanner();

        void close();
        void config(OutputPointsProperties& properties, float pitch);
        void config(OutputVectorsProperties);
        void exit();
        void finalize();
        bool isDone();
        bool isWaitingEvent();
        void lock();
        /*void output(PointList);
        void output(PointList, OutputPointsPropertiesW);
        void output(VectorList);
        void output(VectorList, OutputVectorsProperties);*/
        static std::vector<ScannerInfo> scanners();
        void unlock();
        void wait(float);
        void wait(WaitEvent);
        
        PointParametersWrapper getManagedPointParameters();
        void releaseManagedPointParameters();
        void* getManagedObject();
        void releaseManagedObject();

        void collect();

    };

}