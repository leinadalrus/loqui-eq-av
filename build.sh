#!/bin/bash

code="$PWD"
opts=-g
cd output > /dev/null
g++ $opts $code/loqui_src_main.cpp -o loqui
cd $code > /dev/null
