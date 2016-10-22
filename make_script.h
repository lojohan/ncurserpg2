#!/bin/bash

g++ -c ./Main.cpp
g++ -c ./entities/entityclass/Entity.cpp
g++ -c ./game/Game.cpp

g++ -o RPG *.o

rm *.o

mv ./RPG ./output/

