#include "FunctionPointerStuff.h"

void teleportEntity(Entity * e1, Entity * e2) {
    e1->setY(10);
}

void doNothing(Entity * e1, Entity * e2) {
}

void changeColor(Entity * e1, Entity * e2) {
    e1->setColor(7);
}
