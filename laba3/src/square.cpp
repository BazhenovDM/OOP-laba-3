#include "../include/square.h"
#include <cmath>

Square::Square(): Figure(4){}

Square::operator double() const{
    // Площадь вычисляем по формуле Гаусса
    double s = 0;
    for (size_t i = 0; i < 3; ++i){
        s += this->points[i].getX() * this->points[i + 1].getY() - this->points[i + 1].getX() * this->points[i].getY();
    }
    s = 0.5 * fabs(s + this->points[3].getX() * this->points[0].getY() - this->points[0].getX() * this->points[3].getY());
    return s;
}

Point Square::getCenter() const{
    double cx = 0, cy = 0;
    for (auto& el : this->points){
        cx += el.getX();
        cy += el.getY();
    }
    return Point(0.25 * cx, 0.25 * cy);
}

bool Square::isCorrect() const{
    if (this->length != 4){
        return false;
    }
    
    double x1, x2, x3, x4, y1, y2, y3, y4;
    
    x1 = this->points[0].getX();
    x2 = this->points[1].getX();
    x3 = this->points[2].getX();
    x4 = this->points[3].getX();

    y1 = this->points[0].getY();
    y2 = this->points[1].getY();
    y3 = this->points[2].getY();
    y4 = this->points[3].getY();
    
    const double EPS = 1e-3;

    double d1 = std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2);
    double d2 = std::pow(x3 - x2, 2) + std::pow(y3 - y2, 2);
    double d3 = std::pow(x4 - x3, 2) + std::pow(y4 - y3, 2);
    double d4 = std::pow(x1 - x4, 2) + std::pow(y1 - y4, 2);

    if (std::fabs(d1 - d2) > EPS || std::fabs(d2 - d3) > EPS || std::fabs(d3 - d4) > EPS){
        return false;
    }
    double diag1 = std::pow(x3 - x1, 2) + std::pow(y3 - y1, 2);
    double diag2 = std::pow(x4 - x2, 2) + std::pow(y4 - y2, 2);

    if (std::fabs(diag1 - diag2) > EPS){
        return false;
    }
    bool perpendicular =
        std::fabs((x2-x1)*(x3-x2) + (y2-y1)*(y3-y2)) < EPS &&
        std::fabs((x3-x2)*(x4-x3) + (y3-y2)*(y4-y3)) < EPS &&
        std::fabs((x4-x3)*(x1-x4) + (y4-y3)*(y1-y4)) < EPS &&
        std::fabs((x1-x4)*(x2-x1) + (y1-y4)*(y2-y1)) < EPS;

    return perpendicular;

}