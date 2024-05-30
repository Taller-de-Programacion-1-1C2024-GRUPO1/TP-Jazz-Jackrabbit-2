#!/bin/bash
sudo apt-get install libgtest-dev
sudo apt-get install cmake
mkdir build
cd build
sudo cmake ..
sudo make install -j4
./tests/tests
