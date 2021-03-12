#ifndef _FOR_IMC_SHAPES_SHAPESTORE_H_
#define _FOR_IMC_SHAPES_SHAPESTORE_H_

#include "shape.h"
#include "visitor.h"
#include <vector>
#include <memory>

namespace shapes {

class ShapeStore
{
    public:
        void AddShape(std::shared_ptr<Shape> shape)
        {
            _store.push_back(shape);
        }

        void AcceptVisit(Visitor &visitor)
        {
            for (auto &shape : _store)
            {
                shape->Accept(visitor);
            }
        }

    private:
        std::vector<std::shared_ptr<Shape>> _store;
};

}

#endif
