#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <boost/function.hpp>

class Entity;

typedef boost::function<void(Entity* entity1, Entity* entity2)> ColFnPtr;
typedef boost::function<void(Entity* entity1, Entity* entity2, int count, int * params)> ColFnPtr_unbound;

typedef boost::function<void(Entity * e, int c, int arr[2], int dt)> MovFnPtr;
typedef boost::function<void(Entity * e, int c, int arr[2], int dt, int count, int * params)> MovFnPtr_unbound;

typedef boost::function<void(Entity* entity1, Entity* entity2)> UseFnPtr;
typedef boost::function<void(Entity* entity1, Entity* entity2, int count, int * params)> UseFnPtr_unbound;

#endif
