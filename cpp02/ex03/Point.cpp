#include "Point.hpp"

Point::Point(void) : _x(0), _y(0) {}

Point::Point(const float x, const float y) : _x(x), _y(y) {}

Point::Point(const Point& other) : _x(other._x), _y(other._y) {}

Point& Point::operator=(const Point& other) {
    // Since _x and _y are const, we cannot reassign them
    // This assignment operator should not be used for const members
    // We implement it for Orthodox Canonical Form compliance, but it does nothing
    (void)other;
    return *this;
}

Point::~Point(void) {}

Fixed Point::getX(void) const {
    return this->_x;
}

Fixed Point::getY(void) const {
    return this->_y;
}