#include "../entityheaders/MovableEntity.h"

void MovableEntity::move(int arr[2]) {
    this->setX(arr[0]);
    this->setY(arr[1]);
}
