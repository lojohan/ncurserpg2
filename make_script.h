#!/bin/bash

g++ -c ./Main.cpp

g++ -c ./entities/entityclass/Entity.cpp
g++ -c ./entities/entityclass/Tile.cpp
g++ -c ./entities/entityclass/Player.cpp

g++ -c ./map/Map.cpp

g++ -c ./physics/Physics.cpp

g++ -c ./game/Game.cpp

g++ -c ./utilities/UtilityFunctions.cpp


g++ -o RPG *.o  -lncursesw

rm *.o

mv ./RPG ./output/

