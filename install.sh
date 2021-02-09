#!/bin/bash

#SDL2
sudo apt-get install libsdl2-dev libsdl2-2.0-0 -y
#SDL Image
sudo apt-get install libjpeg-dev libwebp-dev libtiff5-dev libsdl2-image-dev libsdl2-image-2.0-0 -y
#SDL Mixer
sudo apt-get install libmikmod-dev libfishsound1-dev libsmpeg-dev liboggz2-dev libflac-dev libfluidsynth-dev libsdl2-mixer-dev libsdl2-mixer-2.0-0 -y
#SDL Fonts
sudo apt-get install libsdl2-ttf-dev

#QT
sudo apt-get install qt5-default

#LUA
sudo apt-get install lua5.3 liblua5.3-dev

mkdir build
cd build

#yaml
wget https://github.com/jbeder/yaml-cpp/archive/yaml-cpp-0.6.3.zip
unzip yaml-cpp-0.6.3.zip
cd yaml-cpp-yaml-cpp-0.6.3/
mkdir build
cd build
cmake ..
make install
sudo make install
cd ..