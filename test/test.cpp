// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <list>

#include "../ipg-marking-library-wrapper/Scanner.h"
#include "../ipg-marking-library-wrapper/PointParameters.h"
#include "../ipg-marking-library-wrapper/PointList.h"
#include "../ipg-marking-library-wrapper/PointWrapper.h"

using namespace std;
using namespace ipg_marking_library_wrapper;

int main() {
    auto prova = Scanner::scanners();
    string err;

    auto s = new Scanner(prova[0].getName(), true, Units::MICRONS, err);
    OutputPointsProperties pointparam(0.001);
    s->config(pointparam, 0.0f);

    float powerpercent = 100.0;
    float width = (float) 1.0f / 300000;
    float dwell = width;
    int numberOfPulses = 200;

    s->clearLaserEntry();
    s->addLaserEntry(dwell, width, powerpercent, numberOfPulses);

    std::list<Point> listOfPoints;
    float pitch = 250;

    int x = 20;
    int y = 20;
    for (int j = 0; j < y; j++) {
        for (int i = 0; i < x; i++) {
            listOfPoints.push_back(Point(pitch*i, pitch*j));
        }
    }

    {
        PointList outputpoint(listOfPoints);

        s->guide(false);
        s->wait(WaitEvent::StartBit);
        s->laser(LaserAction::Enable);
        s->output(outputpoint);
        s->laser(LaserAction::Disable);
    }

    int w = 10;

}