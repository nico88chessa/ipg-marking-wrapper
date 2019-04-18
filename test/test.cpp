// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <list>

#include "../ipg-marking-library-wrapper/Scanner.h"
#include "../ipg-marking-library-wrapper/PointList.h"
#include "../ipg-marking-library-wrapper/Vector.h"
#include "../ipg-marking-library-wrapper/VectorList.h"
#include "../ipg-marking-library-wrapper/PointWrapper.h"
#include "../ipg-marking-library-wrapper/LibraryException.h"
#include "../ipg-marking-library-wrapper/PolygonProperties.h"

using namespace std;
using namespace ipg_marking_library_wrapper;

int main() {

    int numberOfSides = 6;
    float radius = 1;
    Vector vet;
    
    {

        PointWrapper s = vet.getStart();
        PointWrapper e = vet.getEnd();
        std::cout << s << std::endl;
        std::cout << e << std::endl;

        vet.setEnd(Point(1, 2));
        vet.setStart(Point(11, 12));

        std::cout << s << std::endl;
        std::cout << e << std::endl;
    }
    PointWrapper s = vet.getStart();
    PointWrapper e = vet.getEnd();
    std::cout << s << std::endl;
    std::cout << e << std::endl;
    vet.getEnd().setX(23);
    //vet.setEnd(Point(13, 23));
    std::cout << e << std::endl;

    //    PolygonProperties proper(numberOfSides, radius);
    //    PointList list(proper);
    //    int count = list.count();
    //    {
    //        std::list<Point> list2;
    //        for (int i = 0; i < 10; ++i)
    //            list2.push_back(Point((float)i, (float)i));
    //
    //        list.append(list2);
    //        list.element(0).setX(100);
    //        PointWrapper w = list.element(0);
    //        float xt = w.getX();
    //
    //
    //        //Point miao = ciao;
    //        //miao.setX(11);
    //        //Point test = std::move(miao);
    //        //PointWrapper testW = test;
    //        //testW.setZ(50);
    //        //test.setY(20);
    //        //float z = test.getZ();
    //        //float yTestW = testW.getY();
    //        //float xTest = test.getX();
    //        //float xciao = ciao.getX();
    //
    //    }
    //    int c = list.count();
    //    std::cout << list;
    //}

    ////std::vector<ScannerInfo> list = Scanner::scanners();

    ////Point p;
    ////std::cout << p;
    //VectorList vl(prop);
    //int countTemp = vl.count();

    //std::cout << vl;

    //{
    //    std::list<Vector> vlTemp;
    //    
    //    for (int i = 0; i < 10; ++i)
    //        vlTemp.push_back(Vector(Point((float) i, (float) i), Point((float) 100 + i, (float) 100 + i)));
    //    
    //    VectorList vl2(vlTemp);
    //    VectorList vl3(vl2);
    //    //vl3.append(vl2);
    //    vl2.element(0).setStart(Point(7, 6, 5));

    //    std::cout << "Uno" << std::endl;
    //    std::cout << vl2;
    //    std::cout << "Due" << std::endl;
    //    std::cout << vl3;


    //    std::cout << "dopo append" << std::endl;
    //    
    //    /*vet.setStart(Point(10, 10));
    //    vet.setEnd(Point(20, 20));
    //    Vector vet2(vet);
    //    Point v2Start = vet.getStart();
    //    v2Start.setX(5);
    //    Point v2Start2 = vet.getStart();
    //    int pointPerVet = Vector::getPointsPerVector();
    //    p = vet.getStart();
    //    float x = p.getX();
    //    int y = x;*/
    //}

    //std::cout << vl;
    //vl.shift(10, 20, 0);
    //std::cout << "dopo shift" << std::endl;
    //std::cout << vl;
    //int count = vl.count();
    //Point centerVl(vl.center());
    //float x = centerVl.getX();
    //float y = centerVl.getY();
    //vl.shift(10, 0, 0);
    //Point centerVl2(vl.center());
    //x = centerVl2.getX();
    //y = centerVl2.getY();
    //float x2 = centerVl.getX();
    //float y2 = centerVl.getY();

    //PolygonProperties prop(numberOfSides, radius);
    //Point test;
    //PointList listMain;
    //{
    //    PointList list(prop);
    //    std::list<Point> list2;
    //    for (int i = 0; i < 10; ++i)
    //        list2.push_back(Point((float) i, (float) i));
    //    
    //    PointList testList(list2);
    //    int count = testList.count();
    //    testList.append(list);
    //    count = testList.count();
    //    testList.append(testList);
    //
    //    {
    //        PointWrapper el1 = testList.element(1);
    //        el1.setX(10);
    //        PointWrapper el2 = std::move(el1);
    //    }
    //    PointWrapper&& el1 = testList.element(1);
    //    //float x1 = el1.getX();
    //    PointWrapper el2 = testList.element(1);
    //    float x2 = el2.getX();
    //    listMain.append(testList);
    //    //list.shift(0, 0, 0);
    //    //Point c = list.center();
    //    //float x = c.getX();
    //    //float y = c.getY();
    //    //float z = c.getZ();
    //    //int count = list.count();
    //    //for (int i = 0; i < count; ++i) {
    //    //    Point test = list.element(i);
    //    //    float x2 = test.getX();
    //    //    float y2 = test.getY();
    //    //    float z2 = test.getZ();
    //    //    int test10 = 10;
    //    //}
    //}


}

int mainOld() {
    auto prova = Scanner::scanners();
    string err;

    try {
        auto s = new Scanner("laser - 5410ECA7BC1A.local.", true, Units::MICRONS, err);
        OutputPointsProperties pointparam(0.001f);
        s->config(pointparam, 0.0f);

        float powerpercent = 100.0;
        float width = (float) 1.0f / 300000;
        float dwell = width;
        int numberOfPulses = 200;

        s->ppClearLaserEntry();
        s->ppAddLaserEntry(dwell, width, powerpercent, numberOfPulses);

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
    }
    catch (LibraryException& ex) {
        std::string err = ex.what();
        std::cout << err.c_str();
    }


    int w = 10;
    return 0;
}