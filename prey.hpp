#pragma once

#include "character.hpp"

class Arena;

class Prey : public Character {
public:
	Prey(const Point2D& pos) : Character(pos, Prey::getAvailableDirs()) {};

	void move(const Dir& dir);
	void moveAsNpc(const Arena& arena);

private:
	static std::vector<Dir> getAvailableDirs() {
		return {
			{0, 1}, {1, 0}, {0, -1}, {-1, 0},
			{-1, 1}, {1, 1}, {1, -1}, {-1, -1}
		};
	}
};
