#!/bin/bash
echo "Оновлення списку пакетів..."
sudo apt update
echo "Встановлення OpenCV, CMake та компіляторів..."
sudo apt install libopencv-dev cmake gcc g++ -y
echo "Встановлення завершено!"
