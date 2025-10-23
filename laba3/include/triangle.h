#pragma once

#include "figure.h"

class Triangle: public Figure
{   
    public:
        Triangle();
        virtual ~Triangle() = default;
        
        explicit operator double() const override;
        virtual Point getCenter() const override;
        virtual bool isCorrect() const override;
};