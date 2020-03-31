#pragma once

#include <cmath>

struct Point2D {
    double x = 0;
    double y = 0;

    constexpr Point2D() = default;

    constexpr Point2D(double x, double y)
        : x(x)
        , y(y)
    {
    }

    constexpr Point2D& operator+=(const Point2D& rhs)
    {
        this->x += rhs.x;
        this->y += rhs.y;
        return *this;
    }

    constexpr Point2D& operator-=(const Point2D& rhs)
    {
        this->x -= rhs.x;
        this->y -= rhs.y;
        return *this;
    }

    constexpr Point2D& operator*=(double number)
    {
        this->x *= number;
        this->y *= number;
        return *this;
    }

    constexpr double operator*(const Point2D& point2D) const { return x * point2D.x + y * point2D.y; }

    [[nodiscard]] constexpr double cross(const Point2D& rhs) const { return this->x * rhs.y - this->y * rhs.x; }
    [[nodiscard]] Point2D normalize() const { return Point2D { this->x / abs(), this->y / abs() }; }
    [[nodiscard]] double abs() const { return std::sqrt(x * x + y * y); }
};

[[nodiscard]] constexpr Point2D operator+(Point2D lhs, const Point2D& rhs)
{
    lhs += rhs;
    return lhs;
}

[[nodiscard]] constexpr Point2D operator-(Point2D lhs, const Point2D& rhs)
{
    lhs -= rhs;
    return lhs;
}

[[nodiscard]] constexpr Point2D operator*(Point2D lhs, double rhs)
{
    lhs *= rhs;
    return lhs;
}
