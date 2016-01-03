#include "Graph.hpp"
#include <deque>
#include <iostream>
#include <unordered_map>

// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------
void Graph::init(std::initializer_list<InputNode*> nodes)
{
    update(nodes);
}

// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------
void Graph::update(std::initializer_list<InputNode*> nodes)
{
    std::deque<InnerNode*> evalQ;
    for (auto pInputNode : nodes)
    {
        if (nullptr == pInputNode) continue;
        for (auto pInnerNode : pInputNode->getDownstreams())
        {
            if (!pInnerNode->pending4Evaluate()) // here pInnerNode can't be nullptr
            {
                pInnerNode->pending4Evaluate(true);
                evalQ.push_back(pInnerNode);
            }
        }
    }

    while (!evalQ.empty())
    {
        auto pInnerNode = evalQ.front(); // here pInnerNode can't be nullptr
        evalQ.pop_front();

        bool allInputUpdated = true;
        for (auto pNode : pInnerNode->getUpstreams())        
        {
            if (pNode->pending4Evaluate()) // here pNode can't be nullptr
            {
                allInputUpdated = false; 
                break;
            }
        }

        if (allInputUpdated)
        {
#ifdef DEBUG
            std::cout << "-> evaluating node " << pInnerNode->getName() << " ...\n";
#endif
            bool changed = pInnerNode->evaluate();
            pInnerNode->pending4Evaluate(false);
            if (changed)
            {
                for (auto pDownstreamNode : pInnerNode->getDownstreams())
                {
                    if (!pDownstreamNode->pending4Evaluate()) // here pDownstreamNode can't be nullptr
                    {
                        pDownstreamNode->pending4Evaluate(true);
                        evalQ.push_back(pDownstreamNode);
                    }
                }
#ifdef DEBUG
                std::cout << "node value changed to " << pInnerNode->getValue() << "\n";
#endif
            }
            else
            {
#ifdef DEBUG
                std::cout << "node value unchanged" << "\n";
#endif
            }
        }
        else
        {
            evalQ.push_back(pInnerNode);
        }
    }
}

// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------
void Graph2::init(std::initializer_list<InputNode*> nodes)

{
    _evalVec.clear();

    // build indegree map (do not consider performance much as this is one-off)
    std::unordered_map<InnerNode*, unsigned int> indegreeMap;
    std::unordered_set<InnerNode*> totalSet;
    std::unordered_set<InnerNode*> visitSet;
    for (auto pInputNode : nodes)
    {
        if (nullptr == pInputNode) continue;
        for (auto pInnerNode : pInputNode->getDownstreams())
        {
            totalSet.insert(pInnerNode); // here pInnerNode can't be nullptr
            visitSet.insert(pInnerNode);
        }
    }

    while (!visitSet.empty())
    {
        auto iter = visitSet.begin();
        for (auto pInnerNode : (*iter)->getDownstreams()) 
        {
            totalSet.insert(pInnerNode); // here pInnerNode can't be nullptr
            visitSet.insert(pInnerNode);
        }
        visitSet.erase(iter); // iter is still valid here
    }

    for (auto pInnerNode : totalSet) // here pInnerNode can't be nullptr
    {
        auto indegreeNum = pInnerNode->getUpstreams().size();
        indegreeMap[pInnerNode] = indegreeNum;
#ifdef DEBUG
        std::cout << "Indegree of node " << pInnerNode->getName() 
                  << " is " << indegreeNum << "\n";
#endif
    }

    for (auto pInputNode : nodes)
    {
        if (nullptr == pInputNode) continue;
        for (auto pInnerNode : pInputNode->getDownstreams())
        {
            --indegreeMap[pInnerNode];
        }
    }
    
    do
    {
        auto iter = totalSet.begin();
        while (iter != totalSet.end())
        {
            if (indegreeMap[*iter] == 0) 
            {
                _evalVec.push_back(*iter);
                for (auto pDownstreamNode : (*iter)->getDownstreams())
                {
                    --indegreeMap[pDownstreamNode];
                }
                totalSet.erase(iter++);
            }
            else
            {
                ++iter;
            }
        }
    }
    while (!totalSet.empty());

#ifdef DEBUG
    std::cout << "After topological sort of inner nodes:  ";
    for (auto pInnerNode : _evalVec)
    {
        std::cout << pInnerNode->getName() << " ";
    }
    std::cout << "\n";
#endif

    // evaluate
    update(nodes);
}

// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------
void Graph2::update(std::initializer_list<InputNode*> nodes)
{
    for (auto pInputNode : nodes)
    {
        if (nullptr == pInputNode) continue;
        for (auto pInnerNode : pInputNode->getDownstreams())
        {
            pInnerNode->pending4Evaluate(true);
        }
    }

    for (auto pInnerNode : _evalVec) 
    {
        if (pInnerNode->pending4Evaluate())
        {
#ifdef DEBUG
            std::cout << "-> evaluating node " << pInnerNode->getName() << " ...\n";
#endif
            if (pInnerNode->evaluate())
            {
#ifdef DEBUG
                std::cout << "node value changed to " << pInnerNode->getValue() << "\n";
#endif
                for (auto pDownstreamNode : pInnerNode->getDownstreams())
                {
                    pDownstreamNode->pending4Evaluate(true);
                }
            }
            else
            {
#ifdef DEBUG
                std::cout << "node value unchanged" << "\n";
#endif
            }

            pInnerNode->pending4Evaluate(false);
        }
    }
}

