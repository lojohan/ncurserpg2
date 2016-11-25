#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <boost/function.hpp>

enum Input {
    NONE,
    GO_UP,
    GO_DOWN,
    GO_LEFT,
    GO_RIGHT,
    TURN_UP,
    TURN_DOWN, // for what!
    TURN_LEFT,
    TURN_RIGHT,
    USE_KEY,
    PAUSE,
    DEBUG1
};

class Character;

class Entity;

typedef boost::function<void(Entity* entity1, Entity* entity2)> ColFnPtr;
typedef boost::function<void(Entity* entity1, Entity* entity2, int count, int * params)> ColFnPtr_unbound;

typedef boost::function<void(Entity * e, Input input, int arr[2], long dt)> MovFnPtr;
typedef boost::function<void(Entity * e, Input input, int arr[2], long dt, int count, int * params)> MovFnPtr_unbound;

typedef boost::function<void(Entity* entity1, Entity* entity2)> UseFnPtr;
typedef boost::function<void(Entity* entity1, Entity* entity2, int count, int * params)> UseFnPtr_unbound;

typedef boost::function<void(std::vector<Character*> attackers, std::vector<Character*> targets)> AttackFnPtr;

struct Image {
    const wchar_t * img;
    int color;
    int id;
};

#endif
