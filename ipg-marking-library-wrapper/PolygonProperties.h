#pragma once

#include "IpgmlDef.h"

namespace ipg_marking_library_wrapper {

    class PolygonPropertiesPrivate;

    class IPGMARKINGLIBRARYWRAPPER_API PolygonProperties {
    private:
        PolygonPropertiesPrivate* dPtr;

    public:
        PolygonProperties(int numberOfSides, float radius);
        ~PolygonProperties();
        float getNumberOfSides() const;
        float getRadius() const;

        void* getManagedPtr();
        void releaseManagedPtr();

    };

}
