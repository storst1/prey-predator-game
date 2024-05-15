#pragma once

#include "character.hpp"

class Arena;

class Predator : public Character {
public:
	Predator(const Point2D& pos) : Character(pos, Predator::getAvailableDirs()) {};

	void move(const Dir& dir, const std::size_t length);
	void moveAsNpc(const Arena& arena);

private:
	static std::vector<Dir> getAvailableDirs() {
		return {
			{0, 1}, {1, 0}, {0, -1}, {-1, 0}
		};
	}
};

