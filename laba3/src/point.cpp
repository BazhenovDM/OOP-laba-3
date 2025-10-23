#include "../include/point.h"

Point::Point(): x(0), y(0){}

Point::~Point() noexcept{}

Point::Point(double x, double y): x(x), y(y){}

Point::Point(const Point& other): x(other.x), y(other.y){}

Point::Point(Point&& other) noexcept: x(other.x), y(other.y){}

Point Point::operator+(const Point& right) {
    return Point(this->x + right.x,
                 this->y + right.y);
}

Point Point::operator-(const Point& right) {
    return Point(this->x - right.x,
                 this->y - right.y);
}

Point Point::operator+=(const Point& right) {
    this->x += right.x;
    this->y += right.y;
    return *this;
}

Point Point::operator-=(const Point& right) {
    this->x -= right.x;
    this->y -= right.y;
    return *this;
}

double Point::getX() const{
    return this->x;
}

double Point::getY() const{
    return this->y;
}

void Point::setX(double x){
    this->x = x;
}

void Point::setY(double y){
    this->y = y;
}

std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "("<< p.getX() << ", "<< p.getY() << ")" << " ";
    return os;
}
