#ifndef _FOR_IMC_SHAPES_AREA_VISITOR_H_
#define _FOR_IMC_SHAPES_AREA_VISITOR_H_

#include "visitor.h"
#include "circle.h"
#include "rectangle.h"
#include "triangle.h"

namespace shapes {

class AreaVisitor : public Visitor
{
    public:
        double GetTotalArea()
        {
            return _total_area;
        }

        void Visit(Circle &circle) override
        {
            _total_area += circle.GetArea();
        }

        void Visit(Rectangle &rectangle) override
        {
            _total_area += rectangle.GetArea();
        }

        void Visit(Triangle &triangle) override
        {
            _total_area += triangle.GetArea();
        }

    private:
        double _total_area { 0.0 };
};

}

#endif
