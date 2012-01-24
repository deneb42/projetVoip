#!/bin/bash

gcc $1.c -o $1 `pkg-config --cflags --libs gtk+-2.0` -Wall -ansi
./$1
