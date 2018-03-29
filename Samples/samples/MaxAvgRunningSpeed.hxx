#pragma once

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class MaxAvgRunningSpeed
{
public:
    float calcFromOffset(int block, int offset, const vector<int> &metreSplits)
    {
        int first_block_len = metreSplits[block] - offset;

        float max_avg {0.0};
        int total_len {0};
        int high_idx {block};
        float secs {0};

        while (total_len < 1000 && high_idx < metreSplits.size())
        {
            std::cout << "start within block " << block << ", hight_idx " << high_idx << endl;
            if (high_idx == block)
            {
                std::cout << "start within block " << high_idx << endl;
                total_len += first_block_len;
                secs += (5.0 * first_block_len) / metreSplits[block];
                ++high_idx;
                std::cout << "total_len: " << total_len << " secs: " << secs << endl;
            }
            else
            {
                total_len += metreSplits[high_idx++];
                secs += 5;
                std::cout << "total_len: " << total_len << " secs: " << secs << endl;
            }
        }
        if (total_len < 1000 && high_idx == metreSplits.size())
        {
            std::cout << "cannot find, return 0" << endl;
            return 0;
        }

        int exceed = total_len-1000;
        --high_idx;

        max_avg = 1000 / (secs - (5.0 * exceed) / metreSplits[high_idx]);
        std::cout << "avg of first 1000: " << max_avg << endl;
        for (int i = 1; i <= exceed; ++i)
        {
            float temp = (1000 + i) / (secs - 5.0 * (exceed-i) / metreSplits[high_idx]);
            if (max_avg < temp)
            {
                max_avg = temp;
            }
        }
        ++high_idx;
        for (; high_idx < metreSplits.size(); ++high_idx)
        {
            std::cout << "high_idx " << high_idx << endl;
            for (int i = 1; i <= metreSplits[high_idx]; ++i)
            {
                ++total_len;
                secs += (5.0 * i / metreSplits[high_idx]);
                float temp = total_len / secs;
                if (max_avg < temp)
                {
                    max_avg = temp;
                }
            }
        }
        return max_avg;
    }

    float calculateFastestKilometreSpeed(const vector<int> &metreSplits)
    {
        float max_avg {0.0};
        for (int i = 0; i < metreSplits.size(); ++i)
        {
            for (int j = 0; j < metreSplits[i]; ++j)
            {
                cout << "calc from block " << i << " offset " << j << endl;
                float temp = calcFromOffset(i, j, metreSplits);
                if (temp > max_avg)
                {
                    max_avg = temp;
                }
            }
        }
        return max_avg;
    }
};

