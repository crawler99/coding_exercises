#ifndef FOR_IMC_SHAPES_RECTANGLE_HXX_
#define FOR_IMC_SHAPES_RECTANGLE_HXX_

#include "shape.h"

namespace shapes {

class Rectangle : public Shape
{
    public:
        Rectangle(double length, double width) : _length(length), _width(width)
        {
        }

        Rectangle(const Rectangle &c) = default;
        Rectangle(Rectangle &&c) = default;
        Rectangle& operator= (const Rectangle& c) = default;
        Rectangle& operator= (Rectangle &&c) = default;
        ~Rectangle() = default;

        double GetArea() const
        {
            return _length * _width;
        }

        void Accept(Visitor &visitor) override
        {
            visitor.Visit(*this);
        }

    private:
        double _length { 0.0 };
        double _width { 0.0 };
};

}

#endif
