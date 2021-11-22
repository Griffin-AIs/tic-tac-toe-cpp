#!/bin/bash

if [[ ! -d "build" ]]
then
    mkdir build
fi

cd build
g++ "../main.cpp" -o "build.exe"
cd ..
