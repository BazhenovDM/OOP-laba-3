#pragma once
#include <vector>
#include "figure.h"

class Array {
private:
    std::vector<Figure*> data;
public:
    Array() = default;
    ~Array();
    Array(const Array&) = delete;
    Array& operator=(const Array&) = delete;

    void push_back(Figure* f);
    Figure* at(std::size_t idx) const;
    Figure* operator[](std::size_t idx) const noexcept;
    std::size_t size() const noexcept;
    bool removeAt(std::size_t idx);
    void clear() noexcept;
    double totalArea() const noexcept;
    void printAll() const;
};
