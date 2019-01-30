creazione wrapper da C# / C++ usando CLI

Ambiente di sviluppo: Visual Studio 2015
.NET Framework target: 4.5.2

1. File - New Project - Visual C++ - CLR - Class Library (IMPORTANTE selezionare NET 4.5.2)

2. Solution Explorer -> Project Properties
impostare le seguenti proprieta' (per tutte le configurazioni e piattaforme)
General
    .NET Target Framework Versione: verificare che sia 4.5.2
    Configuration Type: Dynamic Library (.dll)
    Common Language Runtime Support: /clr
Debugging
    Command: qui va agganciato l'eseguibile di test che verra' generato successivamente
C/C++
    Preprocessor
        Preprocessor Definition: aggiungere la direttiva da usare nel blocco #ifdef #define #endif del codice

Linker
    Advanced
        NoEntryPoint: Yes (indica che nella DLL non c'è un main())


Una volta configurato il progetto, agganciare la DLL da wrappare
Nome progetto -> tasto DX -> Add -> Reference -> Browser (selezionare la DLL)
Nota: la DLL e' importata se il .NET target Framework e' uguale o compatibile alla versione utilizzata per
compilare la DLL
