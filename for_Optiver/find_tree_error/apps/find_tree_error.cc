#pragma once

#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

bool IsValidEdgeInput(const string& edge)
{
    return (edge.size() == 5) &&
           (edge[0] == '(') &&
           (edge[2] == ',') &&
           (edge[4] == ')') &&
           (edge[1] >= 'A') && (edge[1] <= 'Z') &&
           (edge[3] >= 'A') && (edge[3] <= 'Z') &&
           (edge[1] != edge[3]);
}

string GenSExpr(char node, const unordered_map<char, set<char>> &adjMap, set<char> &visitedSet)
{
    if (!visitedSet.insert(node).second)
    {
        return "";
    }

    string sExpr = string("(") + node;

    auto it = adjMap.find(node);
    if (it == adjMap.end())  // Reaching leave node.
    {
        return sExpr + ")";
    }

    auto& children = it->second;
    for (auto& child : children)  // Iterate children in lexicographical order.
    {
        auto subSExpr = GenSExpr(child, adjMap, visitedSet);
        if (subSExpr.empty())
        {
            return "";
        }
        sExpr += subSExpr;
    }
    return sExpr + ")";
}

vector<string> Tokenize(const string& text, char sep)
{
    vector<string> tokens;
    size_t start = 0, end = 0;
    while ((end = text.find(sep, start)) != string::npos)
    {
        tokens.push_back(text.substr(start, end - start));
        start = end + 1;
    }
    tokens.push_back(text.substr(start));
    return tokens;
}

/**
 * Problem: read 1 line from stdin with format "(A,B) (A,C) (B,D) ...", each (X,Y) means Y is a child of X in a binary tree.
 *    1) If the construction of binary tree fails, print the highest-level error ("E1" -> downto -> "E5").
 *          - E1: invalid input format
 *          - E2: duplicate input
 *          - E3: a node has more than 2 children
 *          - E4: multiple roots
 *          - E5: there is cycle in the tree
 *    2) If the construction of binary tree succeeds, print the S-Expression of the whole tree. S-Expression is defined as
 *          "(nodeVal(s-Expr-of-left-child)(s-Expr-of-right-child))" where children's s-Expr are appended according to the
 *          lexical order of each child.
 */
int main()
{
    string line;
    getline(cin, line);
    auto inputEdges = Tokenize(line, ' ');
    if (inputEdges.empty())
    {
        cout << "E1";
        return 0;
    }

    unordered_map<char, set<char>> adjMap;
    unordered_map<char, pair<int, int>> degreesMap;
    set<string> errSet;
    for (auto &edge : inputEdges)
    {
        // Check intput format.
        if (!IsValidEdgeInput(edge))
        {
            errSet.insert("E1");
            continue;
        }

        // Check duplicate pairs from input.
        auto& children = adjMap[edge[1]];
        if (!children.insert(edge[3]).second)
        {
            errSet.insert("E2");
            continue;
        }

        // Check parent has more than two childen.
        if (children.size() > 2)
        {
            errSet.insert("E3");
        }
        else
        {
            ++degreesMap[edge[1]].first;   // Increase out degrees
            ++degreesMap[edge[3]].second;  // Increase in degrees
        }
    }

    if (!errSet.empty())
    {
        cout << *errSet.begin();
        return 0;
    }

    // Check multiple roots.
    char root = ' ';
    for (auto& node : degreesMap)
    {
        if (node.second.second == 0)
        {
            if (root != ' ')
            {
                cout << "E4";
                return 0;
            }
            root = node.first;
        }
    }

    // DFS the tree from a beginning node, if a node is visited twice or
    // if the total visited node number is less than adjMap.size(), there
    // must be cycle. Notice that in the latter case, the cycle is separated
    // from current tree which is being traversed.
    set<char> visitedSet;
    string sExpr = GenSExpr(root, adjMap, visitedSet);
    if (!sExpr.empty() && (visitedSet.size() == degreesMap.size()))
    {
        cout << sExpr;
    }
    else
    {
        cout << "E5";
    }

    return 0;
}