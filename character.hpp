#pragma once

#include <vector>

#include "point2d.hpp"


class Character {
public:
	Character(const Point2D& pos, std::vector<std::pair<int, int>> available_dirs) :
		pos(pos), available_dirs(available_dirs) {}
	virtual ~Character() = default;

	const Point2D& getPos() const { return pos; }
	const std::vector<Dir>& getAvailableDirsMember() const { return available_dirs; }

protected:
	Point2D pos{};
	const std::vector<Dir> available_dirs;
};