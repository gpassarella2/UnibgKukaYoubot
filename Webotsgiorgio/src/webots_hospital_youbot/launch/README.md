# File di lancio

## Variabili 

- ```package_dir: ```contiene il path del package
- ```robot_description: ```contiene in una stringa il contenuto del file ```.urdf```  

## WebotsLauncher 
- Contiene il percorso del file di simulazione ```.wbt```

## Node 
Contiene la configurazione dei nodi ROS da mandare in esecuzione nel file di lancio
- Nodi per tf_static_broadcaster
- Nodi ROS

## WebotsController 
Contiene il nome del robot in simulazione e ad esso è associato la descrizione del 
file ```.urdf``` che si vuole utilizzare 
