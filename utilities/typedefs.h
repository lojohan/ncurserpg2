#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <boost/function.hpp>

class Entity;

typedef void (*ColFnPtr)(Entity* entity1, Entity* entity2);
typedef void (*MovFnPtr)(Entity * e, int c, int arr[2], int dt);
typedef void (*UseFnPtr)(Entity* entity1, Entity* entity2);

#endif
