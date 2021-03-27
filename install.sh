#!/bin/bash
mkdir build
cd build
cmake .. && make
sudo cp SimpList /usr/local/bin
