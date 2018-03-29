#pragma once

#include <string>
#include <vector>
#include <iostream>

/* Probolem:
 * Given a char matrix, find “OPTIVER” in each row and column, both in forward and backward char order.
 * Output the total numer of found items.
 */

class FindStrInMatrix
{
public:
    int find(const std::vector<std::string> &matrix)
    {
        int rst {0};

        if (matrix.empty())
        {
            return rst;
        }

        std::string target1("OPTIVER");
        std::string target2("REVITPO");

        auto find_row = [&](const std::string &row)
        {
            if (row.empty()) return;
            for (int pos = 0; pos < row.length();)
            {
                if (row[pos] == 'O')
                {
                    if (row.substr(pos, target1.length()) == target1)
                    {
                        ++rst;
                        pos += target1.length() - 1;
                        continue;
                    }
                }
                else if (row[pos] == 'R')
                {
                    if (row.substr(pos, target2.length()) == target2)
                    {
                        ++rst;
                        pos += target2.length() - 1;
                        continue;
                    }
                }
                ++pos;
            }
        };

        for (auto &s : matrix)
        {
            find_row(s);
        }

        for (int i = 0; i < matrix[0].length(); ++i)
        {
            std::string column("");
            for (auto &s : matrix)
            {
                column += s[i];
            }
            find_row(column);
        }

        return rst;
    }
};

