#!/bin/bash
g++ main.cpp -o AppBirthday.exe `pkg-config --libs --cflags gtk+-3.0` -export-dynamic 

