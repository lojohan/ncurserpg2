/*
 * IOAdapter.h
 *
 *  Created on: Nov 24, 2016
 *      Author: antolss
 */

#ifndef UI_UI_H_
#define UI_UI_H_

class Entity;
#include <string>
#include <vector>

class UI {
public:
	virtual ~UI() {};

	virtual void init() = 0;

	virtual void update(long dt)= 0;

	virtual int playerInput() = 0;

	virtual void displayDialogue(Entity * e1, Entity * e2, std::string dialogue) =0;

	virtual int selectOption(const std::vector<std::string> &options) =0;

	virtual void displayDebug1() =0;
};

#endif /* UI_UI_H_ */
