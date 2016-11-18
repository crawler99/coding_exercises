#include "Graph.hpp"
#include "time.h"
#include <iostream>

// --------------------------------------------------------------------
// This is a class to represent an inner (computational) node in a DAG
// whose value is the sum of all the upstream values
// --------------------------------------------------------------------
class Add : public InnerNode
{
    using InnerNode::InnerNode;  // inherit constructors

public:
    bool evaluate() override FORCE_INLINE
    {
        auto old = _value;
        _value = 0;
        for (auto pNode : _upstreams)
        {
            _value += pNode->getValue();
        }
        return (_value != old);
    }
};

// --------------------------------------------------------------------
// This is a class to represent an inner (computational) node in a DAG
// whose value is the product of all the upstream values
// --------------------------------------------------------------------
class Multiply : public InnerNode
{
    using InnerNode::InnerNode;  // inherit constructors

public:
    bool evaluate() override FORCE_INLINE
    {
        auto old = _value;
        _value = 1;
        for (auto pNode : _upstreams)
        {
            _value *= pNode->getValue();
        }
        return (_value != old);
    }
};

// --------------------------------------------------------------------
// A simple timer for performance testing
// --------------------------------------------------------------------
class Duration
{
public:
    Duration()
    {
        clock_gettime(CLOCK_REALTIME, &_start);
    }

    ~Duration()
    {
        clock_gettime(CLOCK_REALTIME, &_end);
        std::cout << "\nDuration: "
                  << NANOSECS_PER_SEC * (_end.tv_sec - _start.tv_sec) + (_end.tv_nsec - _start.tv_nsec) << "ns\n";
    }

private:
    constexpr static int NANOSECS_PER_SEC { 1000 * 1000 * 1000 };

    timespec _start;
    timespec _end;
};

// --------------------------------------------------------------------
// Test impl of Graph
// --------------------------------------------------------------------
template <class GraphT>
class GraphTest
{
public:
    GraphTest(const std::string &name) : _name(name) {}

    void test()
    {
        std::string tempStr(_name.size() + 20, '=');
        std::cout << "\n" << tempStr << "\n";
        std::cout << "Running test \"" << _name << "\"";
        std::cout << "\n" << tempStr << "\n";

        // input nodes
        InputNode input1("Input1", 1);
        InputNode input2("Input2", 2);
        InputNode input3("Input3", 3);
        InputNode input4("Input4", 4);
        InputNode input5("Input5", 5);

        // inner nodes
        Add add1("Add1", {&input1, &input2, &input3});
        Multiply mul1("Mul1", {&add1, &input3, &input4});
        Add add2("Add2", {&input3, &mul1, &input5});

        // start testing
#ifdef DEBUG
        unsigned int step = 0;
        std::cout << "\n[" << ++step << "] Init 5 input nodes with value {1, 2, 3, 4, 5} ...\n";
#endif
        _graph.init({&input1, &input2, &input3, &input4, &input5});

        Duration duration; // record time cost, exluding the init() process

#ifdef DEBUG
        std::cout << "\n[" << ++step << "] Exchange input1 and input2 to become {2, 1, 3, 4, 5} ...\n";
#endif
        input1.setValue(2);
        input2.setValue(1);
        _graph.update({&input1, &input2});

#ifdef DEBUG
        std::cout << "\n[" << ++step << "] Exchange input3 and input4 to become {2, 1, 4, 3, 5} ...\n";
#endif
        input3.setValue(4);
        input4.setValue(3);
        _graph.update({&input3, &input4});

#ifdef DEBUG
        std::cout << "\n[" << ++step << "] Exchange input1 and input2, set new value to input5 to become {1, 2, 4, 3, 6} ...\n";
#endif
        input1.setValue(1);
        input2.setValue(2);
        input5.setValue(6);
        _graph.update({&input1, &input2, &input5});

#ifdef DEBUG
        std::cout << "\n[" << ++step << "] Do nothing but pass three input nodes to update() in the order {input4, input3, input2} ...\n";
#endif
        _graph.update({&input4, &input3, &input2});
    }

private:
    std::string _name;
    GraphT      _graph;
};

// --------------------------------------------------------------------
// Construct a test graph and do some operations
// --------------------------------------------------------------------
int main()
{
    GraphTest<Graph> gTest1("Graph_test");
    GraphTest<Graph2> gTest2("Graph2_test (topological sort)");

    gTest1.test();
    gTest2.test();

    return 0;
}

