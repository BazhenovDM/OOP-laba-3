#pragma once
#include <iostream>

class Point
{
    protected:
        double x, y;

    public:
        Point();
        Point(double x, double y);
        Point(const Point& other);
        Point(Point&& other) noexcept;
        ~Point() noexcept;
        Point& operator=(const Point&) = default;

        double getX() const;
        double getY() const;
        void setX(double x);
        void setY(double y);

        Point operator+(const Point& right);
        Point operator-(const Point& right);
        Point operator+=(const Point& right);
        Point operator-=(const Point& right);

        friend std::ostream& operator<<(std::ostream& os, const Point& p);

};