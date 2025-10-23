#include "../include/figure.h"
#include <vector>
#include <cmath>
#include <algorithm>


Figure::Figure(): length(1), points(1){};

Figure::Figure(size_t n): length(n), points(n){};

std::ostream& operator<<(std::ostream& os, const Figure& p) {
    for (auto el : p.points){
        os << "("<< el.getX() << ", "<< el.getY() << ")" << " ";
    }
    return os;
}

std::istream& operator>>(std::istream& is, Figure& p) {
    for (size_t i = 0; i != p.length; ++i){
        double x, y;
        is >> x >> y;
        p.points[i].setX(x);
        p.points[i].setY(y);
    }
    return is;
}

Figure& Figure::operator=(const Figure& other) {
    if (this != &other) {
        this->points = other.points;
        this->length = other.length;
    }
    return *this;
}

Figure& Figure::operator=(Figure&& other) noexcept {
    if (this != &other) {
        this->points = std::move(other.points);
        this->length = other.length;
        other.length = 0;
    }
    return *this;
}

bool Figure::operator==(const Figure& other) const {
    const double EPS = 1e-3;

    if (this->length != other.length) return false;

    std::vector<Point> p1 = this->points;
    std::vector<Point> p2 = other.points;

    auto cmp = [EPS](const Point& a, const Point& b) {
        if (fabs(a.getX() - b.getX()) > EPS)
            return a.getX() < b.getX();
        return a.getY() < b.getY();
    };

    sort(p1.begin(), p1.end(), cmp);
    sort(p2.begin(), p2.end(), cmp);

    for (size_t i = 0; i < length; ++i) {
        if (fabs(p1[i].getX() - p2[i].getX()) > EPS ||
            fabs(p1[i].getY() - p2[i].getY()) > EPS)
            return false;
    }
    return true;
}
