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

        size_t GetShapeNum()
        {
            return _areas.size();
        }

        std::vector<double> GetIndividualAreas()
        {
            return _areas;
        }

        void Visit(Circle &circle) override
        {
            double area = circle.GetArea();
            _areas.push_back(area);
            _total_area += area;
        }

        void Visit(Rectangle &rectangle) override
        {
            double area = rectangle.GetArea();
            _areas.push_back(area);
            _total_area += area;
        }

        void Visit(Triangle &triangle) override
        {
            double area = triangle.GetArea();
            _areas.push_back(area);
            _total_area += area;
        }

    private:
        double _total_area { 0.0 };
        std::vector<double> _areas;
};

}

#endif
