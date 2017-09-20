#!/bin/bash

INC_DIR="./include"
SRC_DIR="./src"
g++ -o run $SRC_DIR/main.cpp `find $SRC_DIR -name *.cpp ! -name "main.cpp"` -I$INC_DIR
./run
