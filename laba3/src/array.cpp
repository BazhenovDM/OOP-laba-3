#include "../include/array.h"
#include <iostream>
#include <stdexcept>
#include <iomanip>

Array::~Array() {
    for (Figure* f : data) delete f;
    data.clear();
}

void Array::push_back(Figure* f) {
    if (!f) return;
    data.push_back(f);
}

Figure* Array::at(std::size_t idx) const {
    if (idx >= data.size()) throw std::out_of_range("index");
    return data[idx];
}

Figure* Array::operator[](std::size_t idx) const noexcept {
    return data[idx];
}

std::size_t Array::size() const noexcept {
    return data.size();
}

bool Array::removeAt(std::size_t idx) {
    if (idx >= data.size()) return false;
    delete data[idx];
    data.erase(data.begin() + static_cast<std::ptrdiff_t>(idx));
    return true;
}

void Array::clear() noexcept {
    for (Figure* f : data) delete f;
    data.clear();
}

double Array::totalArea() const noexcept {
    double sum = 0.0;
    for (Figure* f : data) {
        if (!f) continue;
        if (f->isCorrect()) {
            try {
                sum += static_cast<double>(*f);
            } catch (...) {
            }
        }
    }
    return sum;
}

void Array::printAll() const {
    std::cout << std::fixed << std::setprecision(6);
    if (data.empty()) {
        std::cout << "List empty\n";
        return;
    }
    for (std::size_t i = 0; i < data.size(); ++i) {
        Figure* f = data[i];
        if (!f) {
            std::cout << i << ": <null>\n";
            continue;
        }
        std::cout << i << ": " << *f;
        if (f->isCorrect()) {
            double area = 0.0;
            try { area = static_cast<double>(*f); } catch(...) { area = 0.0; }
            Point c = f->getCenter();
            std::cout << " | S=" << area << " | C=" << c << "\n";
        } else {
            std::cout << " | INVALID\n";
        }
    }
}
