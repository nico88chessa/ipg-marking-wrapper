// Test.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include "pch.h"
#include <iostream>
#include <list>

#include "../IpgMarkingLibraryWrapper/Scanner.h"
#include "../IpgMarkingLibraryWrapper/PointParameters.h"
#include "../IpgMarkingLibraryWrapper/PointList.h"
#include "../IpgMarkingLibraryWrapper/PointWrapper.h"

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

int main2() {
    
    //std::cout << "Hello World!\n";
    //auto prova = Scanner::scanners();
    //
    //std::cout << "Lista scanner\n"; 
    //string err;
    //
    //auto s = new Scanner(prova[0].getName(), true, Units::MICRONS, err);
    //std::cout << "Connesso alla testa di scansione\n";
    //{
    //    auto&& te = s->getManagedPointParameters();
    //    te.clearLaserEntries();
    //    std::cout << "Clear laser entries\n";
    //    s->releaseManagedPointParameters();
    //}
    ////s.close();
    //
    //OutputPointsProperties pointProperties(0.001f);

    //s->config(pointProperties, 0.0f);

    //PointParameters testPP = s->getManagedPointParameters();
    //delete s;
    //float le = testPP.getLinkError();
    int maxX = 4000;
    int maxY = 4000;

    std::list<Point> list;
    Point primo(10, 10);
    list.push_back(primo);
    void* ptr = primo.getManagedPtr();
    
    std::cout << ptr << std::endl;
    PointWrapper primoWrapped(ptr);

    std::cout << "X: " << primoWrapped.getX() << " Y: " << primoWrapped.getY() << std::endl;
    
    for (int x = 0; x < maxX; ++x) {
        for (int y = 0; y < maxY; ++y) {
            list.push_back(Point(x,y));
        }
    }

    std::cout << primo.getManagedPtr() << std::endl;
    std::cout << "X: " << primoWrapped.getX() << " Y: " << primoWrapped.getY() << std::endl;

    /*int count = 0;
    for (int x = 0; x < maxX; ++x) {
        for (int y = 0; y < maxY; ++y) {
            std::cout << list.front().getX() << " - " << list.front().getY() << std::endl;
            list.pop_front();
        }
    }*/

    PointList listIpg(list);
    std::cout << "size: " << listIpg.count() << std::endl;
    std::cout << "X: " << primoWrapped.getX() << " Y: " << primoWrapped.getY() << std::endl;

    //auto t2 = s.isDone();
    /*s.lock();
    s.unlock();*/
    //s.exit();
    //s.close();
    for (int i = 0; i < listIpg.count(); ++i)
        std::cout << listIpg.element(i).getX() << " - " << listIpg.element(i).getY() << std::endl;
    
    std::cout << "Bye bye!\n";
    return 0;

}

// Per eseguire il programma: CTRL+F5 oppure Debug > Avvia senza eseguire debug
// Per eseguire il debug del programma: F5 oppure Debug > Avvia debug

// Suggerimenti per iniziare: 
//   1. Usare la finestra Esplora soluzioni per aggiungere/gestire i file
//   2. Usare la finestra Team Explorer per connettersi al controllo del codice sorgente
//   3. Usare la finestra di output per visualizzare l'output di compilazione e altri messaggi
//   4. Usare la finestra Elenco errori per visualizzare gli errori
//   5. Passare a Progetto > Aggiungi nuovo elemento per creare nuovi file di codice oppure a Progetto > Aggiungi elemento esistente per aggiungere file di codice esistenti al progetto
//   6. Per aprire di nuovo questo progetto in futuro, passare a File > Apri > Progetto e selezionare il file con estensione sln
