#ifndef _FOR_IMC_SHAPES_SHAPE_H_
#define _FOR_IMC_SHAPES_SHAPE_H_

namespace shapes {

class Visitor;

class Shape
{
    public:
        virtual void Accept(Visitor &visitor) = 0;
};

}

#endif
