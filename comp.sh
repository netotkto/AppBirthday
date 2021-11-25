#!/bin/bash
g++ main.cpp -o sun `pkg-config --libs --cflags gtk+-3.0` -export-dynamic 

