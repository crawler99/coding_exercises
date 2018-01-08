#include <vector>
#include <algorithm>

class Solution
{
public:
    int maxArea(std::vector<int>& height)
    {
	int maxArea {0};
	for (int i = 0; static_cast<size_t>(i) < height.size() - 1; ++i)
	{
            int highestRightEdge {0};
	    for (int j = height.size() - 1; j > i; --j)
            {
		if (height[j] >= height[i])
                {
                    maxArea = std::max(maxArea, height[i] * (j - i));
                    break;
                }
                if (height[j] > highestRightEdge)
                {
                    highestRightEdge = height[j];
                    maxArea = std::max(maxArea, highestRightEdge * (j - i));
                }
            }
	}
        return maxArea;
    }
};

