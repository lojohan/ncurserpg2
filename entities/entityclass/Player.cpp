#include "../entityheaders/Player.h"

Player::Player(int x, int y, bool solid, const wchar_t * image,
		std::string name, int color, std::vector<ColFnPtr> collision_ptrs,
		std::vector<MovFnPtr> movement_ptrs, std::vector<UseFnPtr> use_ptrs) :
		Entity(x, y, solid, image, name, color, collision_ptrs, movement_ptrs, use_ptrs)
{
	if (party.size() == 0) {
		std::string name = "Anton";
		int maxHp = 100;
		Character * c = new Character(name, maxHp);
		getParty().addCharacter(c);
	}
}
