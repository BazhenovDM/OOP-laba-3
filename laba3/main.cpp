#include <iostream>
#include <sstream>
#include <iomanip>
#include "include/triangle.h"
#include "include/square.h"
#include "include/octagon.h"
#include "include/array.h"

int main() {
    Array arr;

    Triangle* t = new Triangle();
    {
        std::istringstream ss("0 0 1 0 0.5 0.866025");
        ss >> *t;
    }

    Square* s = new Square();
    {
        std::istringstream ss("0 0 1 0 1 1 0 1");
        ss >> *s;
    }

    Octagon* o = new Octagon();
    {
        std::istringstream ss(
            "3.931852 1.517638 3.000000 2.732051 1.482362 2.931852 0.267949 2.000000 "
            "0.068148 0.482362 1.000000 -0.732051 2.517638 -0.931852 3.732051 0.000000"
        );
        ss >> *o;
    }

    arr.push_back(t);
    arr.push_back(s);
    arr.push_back(o);

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "All figures:\n";
    arr.printAll();

    std::cout << "\nTotal area: " << arr.totalArea() << "\n";

    arr.removeAt(1);

    std::cout << "\nAfter removal:\n";
    arr.printAll();

    std::cout << "\nTotal area: " << arr.totalArea() << "\n";

    return 0;
}
