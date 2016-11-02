#include "../entityheaders/NPC.h"

NPC::NPC(int x, int y, bool solid, const wchar_t * image, std::string name, int color,std::vector<ColFnPtr> collision_ptrs, std::vector<MovFnPtr> movement_ptrs, std::vector<UseFnPtr> use_ptrs) : Entity(x, y, solid, image, name,color, collision_ptrs, movement_ptrs, use_ptrs){
    this-> t = 0;
}
