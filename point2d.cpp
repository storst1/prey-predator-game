#include "point2d.hpp"

bool Point2D::operator==(const Point2D& other) const {
	return x == other.x && y == other.y;
}

Point2D Point2D::operator+(const Dir& dir) const
{
	Point2D res(*this);
	res.move(dir);
	return res;
}

int Point2D::distance(const Point2D& other) const {
	return std::abs(x - other.x) + std::abs(y - other.y);
}

float Point2D::distanceReal(const Point2D& other) const
{
	return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2));
}

void Point2D::move(const int x_diff, const int y_diff, const std::size_t velocity)
{
	for (std::size_t i = 0; i < velocity; ++i) {
		x += x_diff;
		y += y_diff;
	}
}

void Point2D::move(const Dir& dir, const std::size_t velocity)
{
	move(dir.first, dir.second, velocity);
}

bool Point2D::isTouching(const Point2D& other) const
{
	return std::abs(other.x - x) <= 1 && std::abs(other.y - y) <= 1;
}
