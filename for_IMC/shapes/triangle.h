#ifndef FOR_IMC_SHAPES_TRIANGLE_HXX_
#define FOR_IMC_SHAPES_TRIANGLE_HXX_

#include "shape.h"
#include <cmath>
#include <stdexcept>

namespace shapes {

class Triangle : public Shape
{
    public:
        Triangle(double edge1, double edge2, double edge3)
        {
            if ((edge1 > (edge2 + edge3)) ||
                (edge2 > (edge1 + edge3)) ||
                (edge3 > (edge1 + edge2)))
            {
                throw std::invalid_argument("Invalid edges provided to construct a triangle.");
            }
            _edge1 = edge1;
            _edge2 = edge2;
            _edge3 = edge3;
        }

        Triangle(const Triangle &c) = default;
        Triangle(Triangle &&c) = default;
        Triangle& operator= (const Triangle& c) = default;
        Triangle& operator= (Triangle &&c) = default;
        ~Triangle() = default;

        double GetArea() const
        {
            double s = (_edge1 + _edge2 + _edge3) / 2;
            return sqrt(s * (s - _edge1) * (s - _edge2) * (s - _edge3));
        }

        void Accept(Visitor &visitor) override
        {
            visitor.Visit(*this);
        }

    private:
        double _edge1 { 0 };
        double _edge2 { 0 };
        double _edge3 { 0 };
};

}

#endif
