# Spiegazione dei file 


## package.xml
File che serve a definire proprietà e dipendenze del package. 
Deve essere incluso nella root di ogni package, nello specifico contine le seguenti informazioni:
- nome package
- numero versione
- autori
- descrizione
- licenze
- dipendenze
- altri package

Il file è vitale per la dichiarazione del sistema di dipendenza dei package, il quale deve assicurarci che i package lavorino
correttamente.
La mancanza o l'incorrezione di dipendenze possono portare problemi quando altri cercano di usare od installare il software.

## setup.cfg
File di configurazione di setup 

- ```[develop] script-dir=$base/lib/<package-name>:``` Questa linea specifica la directory dove gli script saranno allocati durante lo sviluppo.
- ```[install] install-scripts=$base/lib/<package-name>:``` Questa linea definisce la directory dove gli script saranno installati.

## setup.py
File cruciale per definizione dei metadati e per la configurazione dei package sviluppati in Python.
Questo file di setup, sarebbe il `CMakeLists.txt` in `C++`.
Anche questo file è essenziale per la specifica dei seguenti dettagli: 

- ```Infomrazioni dei package: ``` dettagli come il nome del package, numero versione, autore, descrizione, licenze e parole chiavi.
- ```Dipendenze: ``` Questo specifica le dipendenze richiesta dal package per il corretto funzionamento.
- ```Installazione della configurazione: ``` Il file include istruzioni su come installare i package e dove sono posizionati i file di lancio.
- ```Entry Points: ``` Questa sezione consente di definire entry points per gli script dentro il package
- ```File addizionali: ``` Questo include file addizionali che hanno bisogno di essere installati insieme al package.

