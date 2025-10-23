#pragma once

#include "point.h"
#include <vector>

class Figure
{
    protected:
        std::vector<Point> points;
        size_t length;
        
        Figure();
        Figure(size_t n);
    
    public:
        virtual ~Figure() = default;

        virtual Point getCenter() const = 0;
        virtual bool isCorrect() const = 0;
        explicit virtual operator double() const = 0;
        
        friend std::istream& operator>>(std::istream& is, Figure& p);
        friend std::ostream& operator<<(std::ostream& os, const Figure& p);

        Figure& operator=(const Figure& other);
        Figure& operator=(Figure&& other) noexcept;
        bool operator==(const Figure& other) const;
};