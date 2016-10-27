#include "../entityheaders/NPC.h"

NPC::NPC(int x, int y, bool solid, const wchar_t * image, int color,std::vector<ColFnPtr> collision_ptrs, std::vector<MovFnPtr> movement_ptrs) : Entity(x, y, solid, image, color, collision_ptrs, movement_ptrs){
    this-> t = 0;
}
