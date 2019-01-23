// Test.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include "pch.h"
#include <iostream>
#include <list>

#include "../IpgMarkingLibraryWrapper/Scanner.h"
#include "../IpgMarkingLibraryWrapper/PointParameters.h"
#include "../IpgMarkingLibraryWrapper/PointList.h"

using namespace std;
using namespace ipg_marking_library_wrapper;

int main() {
    
    /*std::cout << "Hello World!\n";
    auto prova = Scanner::scanners();
    
    std::cout << "Lista scanner\n"; 
    string err;
    
    auto s = Scanner(prova[0].getName(), true, Units::MICRONS, err);
    std::cout << "Connesso alla testa di scansione\n";
    {
        auto&& te = s.getPointParameters();
        te.clearLaserEntries();
        std::cout << "Clear laser entries\n";
    }*/

    int maxX = 20;
    int maxY = 20;

    std::list<Point> list;
    for (int x = 0; x < maxX; ++x) {
        for (int y = 0; y < maxY; ++y) {
            list.push_back(Point(x, y));
        }
    }

    /*int count = 0;
    for (int x = 0; x < maxX; ++x) {
        for (int y = 0; y < maxY; ++y) {
            std::cout << list.front().getX() << " - " << list.front().getY() << std::endl;
            list.pop_front();
        }
    }*/

    PointList listIpg(list);

    std::cout << "size: " << listIpg.count() << std::endl;

    //auto t2 = s.isDone();
    /*s.lock();
    s.unlock();*/
    //s.exit();
    //s.close();
    for (int i = 0; i < listIpg.count(); ++i)
        std::cout << listIpg.element(i).getX() << " - " << listIpg.element(i).getY() << std::endl;
    
    std::cout << "Bye bye!\n"; 

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
