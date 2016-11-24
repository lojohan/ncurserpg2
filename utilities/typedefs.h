#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <boost/function.hpp>
#include <ncursesw/ncurses.h>

class Character;

class Entity;

typedef boost::function<void(Entity* entity1, Entity* entity2)> ColFnPtr;
typedef boost::function<void(Entity* entity1, Entity* entity2, int count, int * params)> ColFnPtr_unbound;

typedef boost::function<void(Entity * e, int c, int arr[2], int dt)> MovFnPtr;
typedef boost::function<void(Entity * e, int c, int arr[2], int dt, int count, int * params)> MovFnPtr_unbound;

typedef boost::function<void(Entity* entity1, Entity* entity2)> UseFnPtr;
typedef boost::function<void(Entity* entity1, Entity* entity2, int count, int * params)> UseFnPtr_unbound;

typedef boost::function<void(std::vector<Character*> attackers, std::vector<Character*> targets)> AttackFnPtr;

struct Image {
    const wchar_t * img;
    int color;
};

#endif
