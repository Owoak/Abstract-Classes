#pragma once
#include "Animals.h"
#include <iostream>
#include <vector>
#include <utility>
#include "Defines.h"
class World {
private:
	void clearWorld() {
		for (auto row = worldMatrix.begin(); row != worldMatrix.end(); row++) {
			for (auto coll = row->begin(); coll != row->end(); coll++) {
				*coll = ' ';
			}
		}
	}
	size_t Rows; size_t Colls;
	void printAnimalAt(const Animals* ptr, std::pair<int, int> startingPos) {
		for (size_t row = 0; row < ptr->getFace().size(); row++, startingPos.first++) {
			for (size_t coll = 0; coll < ptr->getFace()[row].size(); coll++, startingPos.second++) {
				worldMatrix[startingPos.first][startingPos.second] = ptr->getFace()[row][coll];
			}
			startingPos.second = ptr->getStartingPos().second;
		}
	}
protected:
	Cat* cat;
	Mouse* mouse;
	std::vector<std::vector<char>> worldMatrix;

	World(size_t size) :Rows(size), Colls(size * 2), mouse(new Mouse(15, 15)), cat(new Cat(0, 1)), worldMatrix(Rows, std::vector<char>(Colls, ' ')) {}
	void updateCurrentZoo() {
		if (cat->hasMoved() or mouse->hasMoved()) {
		}
		else {
			return;
		}
		clearWorld();
		for (int row = 0; row < Rows; row++) {
			for (int coll = 0; coll < Colls; coll++) {
				if (cat->hasMoved() and cat->getStartingPos() == std::pair<size_t, size_t>{row, coll}) {
					printAnimalAt(cat, cat->getStartingPos());
				}
				if (mouse->hasMoved() and mouse->getStartingPos() == std::pair<size_t, size_t>{row, coll}) {
					printAnimalAt(mouse, mouse->getStartingPos());
				}
			}
		}
	}
	void printCurrentZoo() {
		updateCurrentZoo();
		for (size_t header = 0; header < worldMatrix[0].size(); header++) {
			std::cout << '_';
		}
		std::cout << std::endl;

		for (auto row = worldMatrix.begin(); row != worldMatrix.end(); row++) {
			for (auto colls = row->begin(); colls != row->end(); colls++) {
				std::cout << *colls;
			}
			std::cout << '|' << std::endl;
		}

		for (size_t header = 0; header < worldMatrix[0].size(); header++) {
			std::cout << '_';
		}
		std::cout << std::endl;
	}
	std::pair<size_t, size_t> getDimensionsWorld() const {
		return std::pair<size_t, size_t>{Rows, Colls};
	}
	virtual ~World() { delete cat; delete mouse; }
};