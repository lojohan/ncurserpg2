#!/bin/bash

g++ -c ./Main.cpp

g++ -c ./entities/entityclass/Entity.cpp
g++ -c ./entities/entityclass/DrawableEntity.cpp
g++ -c ./entities/entityclass/Tile.cpp
g++ -c ./entities/entityclass/MovableEntity.cpp
g++ -c ./entities/entityclass/CollidableEntity.cpp
g++ -c ./entities/entityclass/Player.cpp
g++ -c ./entities/entityclass/CollidableTile.cpp

g++ -c ./map/Map.cpp

g++ -c ./game/Game.cpp

g++ -c ./utilities/UtilityFunctions.cpp


g++ -o RPG *.o  -lncursesw

rm *.o

mv ./RPG ./output/

