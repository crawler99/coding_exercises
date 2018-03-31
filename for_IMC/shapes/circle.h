#ifndef FOR_IMC_SHAPES_CIRCLE_HXX_
#define FOR_IMC_SHAPES_CIRCLE_HXX_

#include "shape.h"

namespace shapes {

class Circle : public Shape
{
    public:
        Circle(double radius) : _radius(radius)
        {
        }

        Circle(const Circle &c) = default;
        Circle(Circle &&c) = default;
        Circle& operator= (const Circle& c) = default;
        Circle& operator= (Circle &&c) = default;
        ~Circle() = default;

        double GetArea() const
        {
            return Pi * _radius * _radius;
        }

        void Accept(Visitor &visitor) override
        {
            visitor.Visit(*this);
        }

    private:
        static constexpr double Pi { 3.1415927 };
        double _radius { 0.0 };
};

}

#endif
