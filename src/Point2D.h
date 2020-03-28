#pragma once
#include <cmath>

struct Point2D {
	double x = 0;
	double y = 0;

	Point2D& operator+=(const Point2D& rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		return *this;
	}

	Point2D& operator-=(const Point2D& rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		return *this;
	}

	Point2D& operator*=(double number)
	{
		this->x *= number;
		this->y *= number;
		return *this;
	}

	double operator*(const Point2D& point2D) const { return x * point2D.x + y * point2D.y; }

	Point2D normalize() { return Point2D{this->x / abs(), this->y / abs()}; }
	double abs() { return std::sqrt(x * x + y * y); }
};

inline Point2D operator+(Point2D lhs, const Point2D& rhs)
{
	lhs += rhs;
	return lhs;
}

inline Point2D operator-(Point2D lhs, const Point2D& rhs)
{
	lhs -= rhs;
	return lhs;
}

inline Point2D operator*(Point2D lhs, double rhs)
{
	lhs *= rhs;
	return lhs;
}
