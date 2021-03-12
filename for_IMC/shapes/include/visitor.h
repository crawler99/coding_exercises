#ifndef _FOR_IMC_SHAPES_VISITOR_H_
#define _FOR_IMC_SHAPES_VISITOR_H_

namespace shapes {

class Circle;
class Rectangle;
class Triangle;

class Visitor
{
    public:
        virtual void Visit(Circle &circle) = 0;
        virtual void Visit(Rectangle &rectangle) = 0;
        virtual void Visit(Triangle &triangle) = 0;
};

}

#endif
