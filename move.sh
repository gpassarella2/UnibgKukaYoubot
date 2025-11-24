#!/bin/bash

while true; do
    echo "---------------------------"
    echo "Seleziona una direzione:"
    echo "1. Avanti"
    echo "2. Dietro"
    echo "3. Destra"
    echo "4. Sinistra"
    echo "5. Diagonale"
    echo "6. Gira Orario"
    echo "7. Gira Antiorario"
    echo "8. Stop"
    echo "9. Esci"
    echo "---------------------------"
    read -p "Scelta: " choice

    case $choice in
        1)
            echo "Muovendo Avanti..."
            ros2 topic pub --once /rover_twist geometry_msgs/msg/Twist "{linear: {x: 0.5, y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: 0.0}}"
            ;;
        2)
            echo "Muovendo Dietro..."
            ros2 topic pub --once /rover_twist geometry_msgs/msg/Twist "{linear: {x: -0.5, y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: 0.0}}"
            ;;
        3)
            echo "Muovendo Destra..."
            ros2 topic pub --once /rover_twist geometry_msgs/msg/Twist "{linear: {x: 0.0, y: -0.5, z: 0.0}, angular: {x: 0.0, y: 0.0, z: 0.0}}"
            ;;
        4)
            echo "Muovendo Sinistra..."
            ros2 topic pub --once /rover_twist geometry_msgs/msg/Twist "{linear: {x: 0.0, y: 0.5, z: 0.0}, angular: {x: 0.0, y: 0.0, z: 0.0}}"
            ;;
        5)
            echo "Muovendo in Diagonale..."
            ros2 topic pub --once /rover_twist geometry_msgs/msg/Twist "{linear: {x: 0.5, y: 0.5, z: 0.0}, angular: {x: 0.0, y: 0.0, z: 0.0}}"
            ;;
        6)
            echo "Girando Orario..."
            ros2 topic pub --once /rover_twist geometry_msgs/msg/Twist "{linear: {x: 0.0, y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: -0.5}}"
            ;;
        7)
            echo "Girando Antiorario..."
            ros2 topic pub --once /rover_twist geometry_msgs/msg/Twist "{linear: {x: 0.0, y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: 0.5}}"
            ;;
        8)
            echo "Stop..."
            ros2 topic pub --once /rover_twist geometry_msgs/msg/Twist "{linear: {x: 0.0, y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: 0.0}}"
            ;;
        9)
            echo "Uscita."
            break
            ;;
        *)
            echo "Scelta non valida."
            ;;
    esac
    echo ""
done
