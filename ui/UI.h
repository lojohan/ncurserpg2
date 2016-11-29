/*
 * IOAdapter.h
 *
 *  Created on: Nov 24, 2016
 *      Author: antolss
 */

#ifndef UI_UI_H_
#define UI_UI_H_

class Entity;
class Battle;
#include <string>
#include <vector>
#include "../utilities/typedefs.h"

class UI {
public:
	virtual ~UI() {};

	virtual void init() {};
	
	virtual void deinit() {};

	virtual void update(long dt) {};
	
	virtual Input playerInput() { return Input::NONE; };

	virtual void displayDialogue(Entity * e1, Entity * e2, std::string dialogue) {};

	virtual int selectOption(const std::vector<std::string> &options) = 0;

	virtual void startBattle(Battle &) {};
	
	virtual void endBattle(Battle &) {};

	virtual void displayDebug1() {};
};

#endif /* UI_UI_H_ */
