#include "../include/octagon.h"
#include <cmath>

Octagon::Octagon(): Figure(8){}

Octagon::operator double() const{
    // Площадь по формуле Гаусса
    double s = 0.0;
    for (size_t i = 0; i < 8; ++i){
        size_t j = (i + 1) % 8;
        s += this->points[i].getX() * this->points[j].getY()
           - this->points[j].getX() * this->points[i].getY();
    }
    return 0.5 * std::fabs(s);
}

Point Octagon::getCenter() const{
    const double EPS = 1e-3;

    double sum = 0.0;
    for (size_t i = 0; i < 8; ++i){
        size_t j = (i + 1) % 8;
        sum += this->points[i].getX() * this->points[j].getY()
             - this->points[j].getX() * this->points[i].getY();
    }
    double area = 0.5 * sum;
    if (std::fabs(area) < EPS) {
        return Point(0.0, 0.0);
    }

    double cx = 0.0, cy = 0.0;
    for (size_t i = 0; i < 8; ++i){
        size_t j = (i + 1) % 8;
        double xi = this->points[i].getX();
        double yi = this->points[i].getY();
        double xj = this->points[j].getX();
        double yj = this->points[j].getY();

        double cross = xi * yj - xj * yi;
        cx += (xi + xj) * cross;
        cy += (yi + yj) * cross;
    }

    cx /= (6.0 * area);
    cy /= (6.0 * area);

    return Point(cx, cy);
}

bool Octagon::isCorrect() const {
    if (this->length != 8) return false;
    const double EPS = 1e-3;

    double d[8];
    for (int i = 0; i < 8; ++i) {
        int j = (i+1) % 8;
        double dx = points[j].getX() - points[i].getX();
        double dy = points[j].getY() - points[i].getY();
        d[i] = dx*dx + dy*dy;
    }

    for (int i = 1; i < 8; ++i) {
        if (std::fabs(d[i] - d[0]) > EPS) return false;
    }

    if (double(*this) < EPS) return false;

    return true;
}
