#include "../include/triangle.h"
#include <cmath>

Triangle::Triangle(): Figure(3){}

Triangle::operator double() const{
    double s = 
        this->points[0].getX() * (this->points[1].getY() - this->points[2].getY()) +
        this->points[1].getX() * (this->points[2].getY() - this->points[0].getY()) +
        this->points[2].getX() * (this->points[0].getY() - this->points[1].getY());
    
    return 0.5 * fabs(s);
}

Point Triangle::getCenter() const{
    double cx = 0, cy = 0;
    for (auto el : this->points){
        cx += el.getX();
        cy += el.getY();
    }
    return Point(cx / 3.0, cy / 3.0);
}

bool Triangle::isCorrect() const{
    if (this->length != 3){
        return false;
    }

    double x1, x2, x3, y1, y2, y3;
    
    x1 = this->points[0].getX();
    x2 = this->points[1].getX();
    x3 = this->points[2].getX();

    y1 = this->points[0].getY();
    y2 = this->points[1].getY();
    y3 = this->points[2].getY();
    
    double d1 = std::pow(x2 - x1, 2) + pow(y2 - y1, 2);
    double d2 = std::pow(x3 - x2, 2) + pow(y3 - y2, 2);
    double d3 = std::pow(x1 - x3, 2) + pow(y1 - y3, 2);

    const double EPS = 1e-3;

    return std::fabs(d1 - d2) < EPS && std::fabs(d2 - d3) < EPS;
}