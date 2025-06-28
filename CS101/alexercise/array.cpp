// 给定一个 n 个元素有序的（升序）整型数组 nums 和一个目标值 target  ，写一个函数搜索 nums 中的 target，如果目标值存在返回下标，否则返回 -1。
#include <vector>
template <typename T>
using vector = std::vector<T>;
class Solution
{
public:
    int search(vector<int> &nums, int target)
    {
        int left = 0;
        int right = nums.size() - 1;
        while (left <= right)
        {
            int middle = (left + right) / 2;
            if (nums[middle] < target)
                left = middle + 1;
            else if (nums[middle] > target)
                right = middle - 1;
            else
                return middle;
        }
        return -1;
    }
};

/*给你一个数组 nums 和一个值 val，你需要 原地 移除所有数值等于 val 的元素。元素的顺序可能发生改变。然后返回 nums 中与 val 不同的元素的数量。

假设 nums 中不等于 val 的元素数量为 k，要通过此题，您需要执行以下操作：

更改 nums 数组，使 nums 的前 k 个元素包含不等于 val 的元素。nums 的其余元素和 nums 的大小并不重要。
返回 k。*/
class Solution
{
public:
    int removeElement(vector<int> &nums, int val)
    {
        int slowIndex = 0;
        for (int fastIndex = 0; fastIndex < nums.size(); fastIndex++)
        {
            if (nums[fastIndex] != val)
            {
                nums[slowIndex] = nums[fastIndex];
                slowIndex++;
            }
        }
        return slowIndex;
    }
};
// 给定一个含有 n 个正整数的数组和一个正整数 s ，找出该数组中满足其和 ≥ s 的长度最小的 连续 子数组，并返回其长度。如果不存在符合条件的子数组，返回 0。
class Solution
{
public:
    int minSubArrayLen(int target, vector<int> &nums)
    {
        int result = INT32_MAX;
        int i = 0;
        int sum = 0;
        int sub = 0;
        for (int j = 0; j < nums.size(); j++)
        {
            sum += nums[j];
            while (sum >= target)
            {
                sub = j - i + 1;
                result = result < sub ? result : sub;
                sum -= nums[i++];
            }
        }
        return result == INT32_MAX ? 0 : result;
    }
};
// 给定一个正整数 n，生成一个包含 1 到 n^2 所有元素，且元素按顺时针顺序螺旋排列的正方形矩阵。
class Solution
{
public:
    vector<vector<int>> generateMatrix(int n)
    {
        int i, j;
        int loop = n / 2;
        vector<vector<int>> nums(n, vector<int>(n, 0));
        int startx = 0, starty = 0, offset = 1, count = 1;
        while (loop--)
        {
            for (j = starty; j < n - offset; j++)
            {
                nums[startx][j] = count++;
            } // j=n-offset;
            for (i = startx; i < n - offset; i++)
            {
                nums[i][j] = count++;
            }
            for (; j > starty; j--)
            {
                nums[i][j] = count++;
            }
            for (; i > startx; i--)
            {
                nums[i][j] = count++;
            }
            startx++;
            starty++;
            offset++;
        }
        if (n % 2 == 1)
        {
            nums[startx][starty] = count;
        }
        return nums;
    }
};