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

// Empty return means we visited a node twice in DFS and it is not a valid tree.
string GenSExpr(char node, const unordered_map<char, set<char>> &adjMap, set<char> &visitedSet)
{
    if (!visitedSet.insert(node).second)
    {
        return "";
    }

    auto it = adjMap.find(node);
    if (it == adjMap.end())  // Reaching leave node.
    {
        return string("(") + node + ")";
    }

    string sExpr;
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
    return string("(") + node + sExpr + ")";
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

    // DFS the tree from a beginning node:
    //  - If no root is found (root == ' '), a cycle exists in current tree and the returned sExpr will be empty.
    //  - Otherwise, if a node is visited twice from root, a cycle exists in current tree and the returned sExpr will be empty.
    //  - Otherwise, if the total visited node number is less than degreesMap.size(), there must a cycle that is separated from current tree.
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