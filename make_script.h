#!/bin/bash

g++ -c ./Main.cpp
g++ -c ./entities/entityclass/Entity.cpp
g++ -c ./game/Game.cpp
g++ -c ./entities/entityclass/DrawableEntity.cpp

g++ -o RPG *.o  -lncurses

rm *.o

mv ./RPG ./output/

