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
            for (int pos = 0; pos < row.length();)
            {
                auto found1 = row.find(target1, pos);
                if (found1 != std::string::npos)
                {
                    ++rst;
                    pos = found1 + target1.length() - 1;
                    continue;
                }
                auto found2 = row.find(target2, pos);
                if (found2 != std::string::npos)
                {
                    ++rst;
                    pos = found2 + target2.length() - 1;
                    continue;
                }
                break;
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

