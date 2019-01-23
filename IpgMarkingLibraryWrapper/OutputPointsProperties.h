#pragma once

#include "IpgmlDef.h"
#include "Enums.h"


namespace ipg_marking_library_wrapper {

    class OutputPointsPropertiesPrivate;

    class IPGMARKINGLIBRARYWRAPPER_API OutputPointsProperties {
    private:
        OutputPointsPropertiesPrivate* dPtr;

    public:
        OutputPointsProperties(void* other);
        OutputPointsProperties(float pulseEnergy);
        OutputPointsProperties(float pulseEnergy, Optimization opt);
        OutputPointsProperties(OutputPointsProperties&& other);
        ~OutputPointsProperties();

        Optimization getOptimization() const;
        float getPulseEnergy() const;

        void* getManagedObject();
    };

}