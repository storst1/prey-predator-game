#pragma once

#include <memory>
#include <iostream>
#include <iomanip>

#include "predator.hpp"
#include "prey.hpp"


class Arena {
public:
	Arena();
	~Arena() = default;

	bool isInBounds(const Point2D& point) const;
	const Point2D& getPreyPos() const { return prey->getPos(); }
	void play();

private:
	bool askForSide() const;
	int askForPreyMove() const;
	std::pair<int, int> askForPredatorMove() const;
	void display() const;

	bool prey_is_npc;
	const int w = 30;
	const int h = 30;
	std::unique_ptr<Predator> predator;
	std::unique_ptr<Prey> prey;
};