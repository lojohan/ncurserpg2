#!/bin/bash

g++ -c ./Main.cpp
g++ -c ./entities/entityclass/Entity.cpp

g++ -o Game Main.o Entity.o

rm *.o

mv ./Game ./output/

