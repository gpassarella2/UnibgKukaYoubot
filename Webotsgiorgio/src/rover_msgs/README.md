# Costruzione messaggi
Tipicamente nella documentazione di ROS i messaggi sono creati a partire da file con estensione `.msg`, `srv` e `action`.

## msg
I file `msg` sono semplici file di testo che descrivono i campi del messaggio ROS. Sono utilizzati
per generare codici sorgenti per messaggi in differenti linguaggi

## srv
I file `srv` descrivono un servizio. Questo è composto da due parti: 
- request
- response
## action
I file `action` descrivono un azione. Questo è composto da tre parti:
- request
- result
- feedback

## idl 
Con metodo standard di ROS per la costruzione dei messaggi non ho il controllo su come questi vengono 
creati. Quindi un'opzione molto valida è quello di utilizzare i file .idl per la creazione delle
interfacce.
Tramite i file .idl posso utilizzare i moduli che devono essere coerenti con quelli definiti in `STRESA`.
