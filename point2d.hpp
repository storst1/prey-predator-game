#pragma once

#include <cstddef>
#include <cmath>

using Dir = std::pair<int, int>;

class Point2D
{
public:
	Point2D(int x = 0, int y = 0) : x(x), y(y) {}
	~Point2D() = default;

	bool operator==(const Point2D& other) const;
	Point2D operator+(const Dir& dir) const;
	int distance(const Point2D& other) const;
	float distanceReal(const Point2D& other) const;
	void move(const int x_diff, const int y_diff, const std::size_t velocity = 1);
	void move(const Dir& dir, const std::size_t velocity = 1);
	const int X() const { return x; }
	const int Y() const { return y; }
	bool isTouching(const Point2D& other) const;

private:
	int x = 0;
	int y = 0;
};
