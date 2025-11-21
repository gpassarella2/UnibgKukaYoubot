#!/bin/bash
# 1. Imposta l'ambiente (che include ROS e il tuo workspace)
source /opt/ros/jazzy/setup.bash
source ./setup.sh

# 2. Esegui il nodo di teleoperazione
echo "Avvio del controllo teleop... (usa w,a,s,d,i,j,k,l per muovere)"

ros2 run webots_hospital_youbot teleop_youbot.py



