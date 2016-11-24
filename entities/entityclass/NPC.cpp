#include "../entityheaders/NPC.h"
#include "../entityheaders/Character.h"

NPC::NPC(int x, int y, bool solid, std::string name, Image image,std::vector<ColFnPtr> collision_ptrs, std::vector<MovFnPtr> movement_ptrs, std::vector<UseFnPtr> use_ptrs)
: Entity(x, y, solid, name,image, collision_ptrs, movement_ptrs, use_ptrs) {
    this-> t = rand() % 75000;

    if(party.size() == 0) {
    	for (int i = 0; i < 10; i++) {
			std::string name = "Doggy";
			int maxHp = 100;
			Character * c = new Character(name, maxHp);
			getParty().addCharacter(c);
    	}
    }
}
