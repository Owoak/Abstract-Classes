#pragma once
#include "World.h"
#include <string>

class RenderEngine final : public World {
private:
public:
	RenderEngine(size_t size) :World(size) {}
	void printZoo() { printCurrentZoo(); }
	void move(std::string animal, Directions direction) {
		if (animal == "cat") {
			cat->movePosition(direction, this->getDimensionsWorld());
		}
		else if (animal == "mouse") {
			mouse->movePosition(direction, this->getDimensionsWorld());
		}
	}
};