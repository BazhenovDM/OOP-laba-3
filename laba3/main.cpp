#include <iostream>
#include "include/six.h"

int main() {
    Six a("123");
    Six b("5");
    Six c = a.add(b);
    if (c.greater(a)) {
        std::cout << "A greater than B\n";
    }
    return 0;
}
