#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "area_visitor.h"
#include "shape_store.h"

using namespace shapes;
using namespace std;

TEST(AreaVisitor, Correctness)
{
    ShapeStore store;

    store.AddShape(make_shared<Circle>(3));
    store.AddShape(make_shared<Circle>(5.5));
    store.AddShape(make_shared<Rectangle>(4, 10));
    store.AddShape(make_shared<Triangle>(3, 4, 5));

    try
    {
        store.AddShape(make_shared<Triangle>(3, 4, 50));
        EXPECT_FALSE(true); // should not reach here
    }
    catch (const std::invalid_argument &e)
    {
    }

    AreaVisitor visitor;
    store.AcceptVisit(visitor);

    // Check correctness.
    double epsilon { 0.00001 };
    EXPECT_EQ(4, visitor.GetShapeNum());
    std::vector<double> my_areas = visitor.GetIndividualAreas();
    std::vector<double> right_areas { 28.2743343, 95.033179175, 40, 6 };
    for (unsigned int i = 0; i < right_areas.size(); ++i)
    {
        EXPECT_NEAR(right_areas.at(i), my_areas.at(i), epsilon);
    }
    EXPECT_NEAR(169.307513475, visitor.GetTotalArea(), epsilon);
}

