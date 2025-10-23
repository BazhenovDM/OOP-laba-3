#pragma once

#include "figure.h"

class Square: public Figure
{   
    public:
        Square();
        virtual ~Square() = default;

        explicit operator double() const override;
        virtual Point getCenter() const override;
        virtual bool isCorrect() const override;
};