#pragma once

#ifdef __GNUC__
#define FORCE_INLINE __attribute__((always_inline))
#else
#define FORCE_INLINE 
#endif

#include <string>
#include <unordered_set>
#include <vector>

// ------------------------------------------------------------------
// This is a class to represent a general node conecept in a DAG
// ------------------------------------------------------------------
class InnerNode;
class Node
{
public:
    std::string getName() const noexcept FORCE_INLINE
    {
        return _name; // move semantic is utilized automatically by C++11
    }

    int getValue() const noexcept FORCE_INLINE
    {
        return _value;
    }    

    void setName(const char *name) noexcept FORCE_INLINE
    {
        _name = std::string(name);
    }

    void addUpstreamNode(Node *pNode) noexcept FORCE_INLINE
    {
        if (nullptr != pNode) _upstreams.insert(pNode);
    }

    void addDownstreamNode(InnerNode *pInnerNode) noexcept FORCE_INLINE
    {
        if (nullptr != pInnerNode) _downstreams.insert(pInnerNode); 
    }

    const std::unordered_set<InnerNode*>& getDownstreams() noexcept FORCE_INLINE
    {
        return _downstreams;
    }

    const std::unordered_set<Node*>& getUpstreams() noexcept FORCE_INLINE
    {
        return _upstreams;
    }

    virtual bool evaluate() = 0;

    virtual bool pending4Evaluate() = 0;

protected:
    int                             _value = 0;
    std::unordered_set<Node*>       _upstreams;   // unordered_set should be faster to search pointers
    std::unordered_set<InnerNode*>  _downstreams; // unordered_set should be faster to search pointers

private:
    std::string             _name;
};

// -------------------------------------------------------------------
// This is a class to represent an input node in a DAG for calculation
// -------------------------------------------------------------------
class InputNode : public Node
{
public: 
    InputNode(const char *name, int value) 
    {
        setName(name);
        _value = value;
    }

    void setValue(int value) noexcept FORCE_INLINE
    {
        _value = value;
    }

    bool evaluate() override FORCE_INLINE
    {
        return true;
    }

    bool pending4Evaluate() override FORCE_INLINE
    {
        return false; // Input node never needs to be evaluated, although
                      // it has a evaluate() method.
    }
};

// --------------------------------------------------------------------
// This is a class to represent an inner (computational) node in a DAG 
// --------------------------------------------------------------------
class InnerNode : public Node
{
public:
    // Disable all the following construction functions so the user
    // is not able to generate a cycle for the DAG.
    InnerNode(const InnerNode&)              = delete;
    InnerNode(InnerNode&&)                   = delete;
    InnerNode& operator = (const InnerNode&) = delete;
    InnerNode& operator = (InnerNode&&)      = delete;

    InnerNode(const char *name, std::initializer_list<Node*> inputs)
    {
        setName(name);
        for (auto pNode : inputs)
        {
            if (nullptr != pNode)
            {
                pNode->addDownstreamNode(this);
            }
            addUpstreamNode(pNode);
        }
    }

    bool pending4Evaluate() override FORCE_INLINE
    {
        return _pending4Evaluate;
    }

    void pending4Evaluate(bool b) FORCE_INLINE
    {
        _pending4Evaluate = b;
    }

private:
    bool _pending4Evaluate = false;
};

// --------------------------------------------------------------------
// This is a class to represent the DAG for calculation
// --------------------------------------------------------------------
class Graph
{
public:
    // This function is used to provide ALL the initial input nodes for the DAG. 
    static void init(std::initializer_list<InputNode*> nodes);

    // This function is used to provide only the updated input nodes for the DAG.
    // And we will re-evaluate the whole graph.
    static void update(std::initializer_list<InputNode*> nodes);
};

// -------------------------------------------------------------------------------------------
// This is a class to represent the DAG, and utilize topological sort to optimize calculation
// -------------------------------------------------------------------------------------------
class Graph2
{
public:
    // This function is used to provide ALL the initial input nodes for the DAG. 
    void init(std::initializer_list<InputNode*> nodes);

    // This function is used to provide only the updated input nodes for the DAG.
    // And we will re-evaluate the whole graph.
    void update(std::initializer_list<InputNode*> nodes);

private:
    std::vector<InnerNode*> _evalVec;
};

