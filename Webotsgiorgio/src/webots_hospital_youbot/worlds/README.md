# Worlds di WEBOTS 
All'interno di questo package sono inseriti i file ```.wbt``` che contengono le informazioni di simulazione.

## Effettuare modifiche 
Per effettuare modifiche sul mondo di simulazione ci sono due modi:

- Farle direttamente in simulazione
- Modificare direttamente il file .wbt

## Modifiche necessarie 
Le modifiche da fare nel mondo di webots:
- Conversione del ```proto node``` del robot in ```base node```.
- Settare il campo ```supervisor``` del nodo robot a ```true```.
- Settare il ```controller``` come ```extern```.
- Varie modifiche sui campi dei sensori.
  
## Supervisor 
Un nodo che ha il campo ```supervisor``` settato a ```true``` ha i permessi per accedere 
a campi veri e propri della simulazione di ```webots```. 
