#pragma once
#include "Defines.h"
#include <vector>
#include <utility>

class AnimalBox {
protected:
	bool hasMoved;
	std::pair<int, int> StaringPos;
	std::pair<int, int> size;
	AnimalBox(int x, int y) :hasMoved(true), StaringPos(x, y), size() {}
	virtual void movePosition(const Directions& direction, const std::pair<size_t, size_t>& dimensions) = 0;
	virtual ~AnimalBox() {}
};

class Animals : public  AnimalBox {
private:
	const std::vector<std::vector<char>> face;
protected:
	Animals(const std::vector< std::vector<char>>& inputFace, int row, int coll) :face(inputFace), AnimalBox(row, coll) {
	}
public:
	virtual void movePosition(const Directions& direction, const std::pair<size_t, size_t>& dimensions) override {
		switch (direction) {
		case Directions::UP:
			if (StaringPos.first > 0) {
				StaringPos.first--;
			}
			break;
		case Directions::DOWN:
			if (StaringPos.first < dimensions.first - 1) {
				StaringPos.first++;
			}
			break;
		case Directions::LEFT: {
			int movedPositins = 0;
			while (StaringPos.second > 0 and movedPositins <= 2) {
				StaringPos.second--;
				movedPositins++;
			}
			break;
		}
		case Directions::RIGHT: {
			int movedPositins = 0;
			while (StaringPos.second < dimensions.second - 1 and movedPositins <= 2) {
				StaringPos.second++;
				movedPositins++;
			}
			break;
		}
		}
		AnimalBox::hasMoved = true;
	}
	const std::pair<int, int>& getStartingPos()const { return StaringPos; }
	const std::vector<std::vector<char>>& getFace()const { return face; }
	virtual ~Animals() {}
	bool& hasMoved() { return AnimalBox::hasMoved; }
};

class Mouse :public Animals {
private:
public:
	Mouse(int row, int coll) :Animals({
		{'~', '~', '(', '_', '_', '^', '-', '>'} }, row, coll) {
		size.first = 1; size.second = 8;
	}
	virtual ~Mouse() {}
};

class Cat :public Animals {
private:
public:
	Cat(int row, int coll) :Animals({
	{'=', '^', '.', '.', '^', '='},
	{' ', ' ', '~', '~', '~', ' '} }, row, coll) {
		size.first = 2; size.second = 6;
	}
	virtual ~Cat() {}
};
