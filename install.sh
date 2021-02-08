#!/bin/bash

#SDL2
sudo apt install libsdl2-dev libsdl2-2.0-0 -y
sudo apt install libjpeg-dev libwebp-dev libtiff5-dev libsdl2-image-dev libsdl2-image-2.0-0 -y
sudo apt install libmikmod-dev libfishsound1-dev libsmpeg-dev liboggz2-dev libflac-dev libfluidsynth-dev libsdl2-mixer-dev libsdl2-mixer-2.0-0 -y
sudo apt-get install libsdl2-ttf-dev

#QT
sudo apt-get install qt5-default

mkdir build
cd build

#yaml
git clone https://github.com/jbeder/yaml-cpp
cd yaml-cpp
mkdir build
cd build
cmake ..
make
sudo make
cd ..
