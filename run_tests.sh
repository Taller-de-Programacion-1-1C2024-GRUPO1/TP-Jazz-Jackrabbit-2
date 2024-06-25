#!/bin/bash
sudo apt-get install -y libgtest-dev
sudo apt-get install -y cmake
mkdir build
cd build
sudo cmake ..
sudo make install -j4
./tests/tests
