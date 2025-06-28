#include <climits>
#include <stack>
#include <queue>
#include <string>
#include <vector>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>
using namespace std;
class Solution
{
public: // 大饼干优先满足胃口大的小孩。
    int findContentChildren(vector<int> &g, vector<int> &s)
    {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int index = s.size() - 1;
        int result = 0;
        for (int i = g.size() - 1; i >= 0; i--)
        {
            if (index >= 0 && g[i] <= s[index])
            {
                index--;
                result++;
            }
        }
        return result;
    }
};

class Solution
{
public:
    int wiggleMaxLength(vector<int> &nums)
    {
        int curdistancediff = 0;
        int prediff = 0;
        int result = 1;
        for (int i = 0; i < nums.size() - 1; i++)
        {
            curdistancediff = nums[i + 1] - nums[i];
            if (curdistancediff > 0 && prediff <= 0 || curdistancediff < 0 && prediff >= 0)
            {
                result++;
                prediff = curdistancediff; // pre记录上一个非平坡
            }
        }
        return result;
    }
};
// 最大连续子数组的和
class Solution
{
public:
    int maxSubArray(vector<int> &nums)
    {
        int result = INT_MIN;
        int count = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            count += nums[i];
            if (count > result)
            {
                result = count;
            }
            if (count < 0)
            {
                count = 0; // 相当于重新选取起始位置。
            }
        }
        return result;
    }
};
// 股票问题
class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        int result = 0;
        for (int i = 1; i < prices.size(); i++)
        {
            result += max(prices[i] - prices[i - 1], 0);
        }
        return result;
    }
};
// 跳跃游戏
class Solution
{
public:
    bool canJump(vector<int> &nums)
    {
        int cover = 0;
        if (nums.size() == 1)
        {
            return true;
        }
        for (int i = 0; i <= cover; i++)
        {
            cover = max(i + nums[i], cover);
            if (cover >= nums.size() - 1)
            {
                return true;
            }
        }
        return false;
    }
};
// 跳跃游戏II最少跳几步
class Solution
{
public:
    int jump(vector<int> &nums)
    {
        if (nums.size() == 1)
        {
            return 0;
        }
        int curdistance = 0;
        int nextdistance = 0;
        int result = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            nextdistance = max(i + nums[i], nextdistance);

            if (i == curdistance)
            {
                if (curdistance != nums.size() - 1)
                {
                    result++;
                    curdistance = nextdistance;
                    if (curdistance >= nums.size() - 1)
                        break;
                }
                else
                {
                    break;
                }
            }
        }
        return result;
    }
};
// 加油站
class Solution
{
public:
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost)
    {
        int cursum = 0;
        int totalSum = 0;
        int start = 0;
        for (int i = 0; i < gas.size(); i++)
        {
            cursum += gas[i] - cost[i];
            totalSum += gas[i] - cost[i];
            if (cursum < 0)
            {
                start = i + 1;
                cursum = 0;
            }
        }
        if (totalSum < 0)
        {
            return -1;
        }
        else
        {
            return start;
        }
    }
};
class Solution
{
public:
    int candy(vector<int> &ratings)
    {
        vector<int> candyVec(ratings.size(), 1);
        int result = 0;
        for (int i = 1; i < ratings.size(); i++)
        {
            if (ratings[i] > ratings[i - 1])
            {
                candyVec[i] = candyVec[i - 1] + 1;
            }
        }
        for (int i = ratings.size() - 2; i >= 0; i--)
        {
            if (ratings[i] > ratings[i + 1])
            {
                candyVec[i] = max(candyVec[i + 1] + 1, candyVec[i]);
            }
        }
        for (int i = 0; i < candyVec.size(); i++)
        {
            result += candyVec[i];
        }
        return result;
    }
};
// 柠檬水找零
class Solution
{
public:
    bool lemonadeChange(vector<int> &bills)
    {
        int five = 0;
        int ten = 0;
        int twenty = 0;

        for (int bill : bills)
        {
            if (bill == 5)
            {
                five++;
            }
            if (bill == 10)
            {
                if (five == 0)
                {
                    return false;
                }

                ten++;
                five--;
            }
            if (bill == 20)
            {
                if (ten > 0 && five > 0)
                {
                    ten--;
                    five--;
                    twenty++;
                }
                else if (five >= 3)
                {
                    five -= 3;
                    twenty++;
                }
                else
                {
                    return false;
                }
            }
        }
        return true;
    }
};
// 最少数量的弓箭引爆气球
class Solution
{
public:
    static bool cmp(const vector<int> &a, const vector<int> &b)
    {
        return a[0] < b[0];
    }
    int findMinArrowShots(vector<vector<int>> &points)
    {
        if (points.size() == 0)
        {
            return 0;
        }
        sort(points.begin(), points.end(), cmp);
        int result = 1;
        for (int i = 1; i < points.size(); i++)
        {
            if (points[i][0] > points[i - 1][1])
            {
                result++;
            }
            else
            {
                points[i][1] = min(points[i][1], points[i - 1][1]);
            }
        }
        return result;
    }
};
// 无重叠区间
class Solution
{
public:
    static bool cmp(const vector<int> &a, const vector<int> &b)
    {
        return a[0] < b[0];
    }
    int eraseOverlapIntervals(vector<vector<int>> &intervals)
    {
        if (intervals.size() == 0)
        {
            return 0;
        }
        sort(intervals.begin(), intervals.end(), cmp);
        int result = 0;
        for (int i = 1; i < intervals.size(); i++)
        {
            if (intervals[i][0] < intervals[i - 1][1])
            {
                intervals[i][1] = min(intervals[i][1], intervals[i - 1][1]);
                result++;
            }
        }
        return result;
    }
};
// 合并区间
class Solution
{
public:
    static bool cmp(const vector<int> &a, const vector<int> &b)
    {
        return a[0] < b[0];
    }
    vector<vector<int>> merge(vector<vector<int>> &intervals)
    {
        vector<vector<int>> result;
        if (intervals.size() == 0)
        {
            return result;
        }
        sort(intervals.begin(), intervals.end(), cmp);
        result.push_back(intervals[0]);
        for (int i = 1; i < intervals.size(); i++)
        {
            if (intervals[i][0] <= result.back()[1])
            {
                result.back()[1] = max(result.back()[1], intervals[i][1]);
            }
            else
            {
                result.push_back(intervals[i]);
            }
        }
        return result;
    }
};
// 单调递增的数字
class Solution
{
public:
    int monotoneIncreasingDigits(int n)
    {
        string strNum = to_string(n);
        int flag = strNum.size(); // 取字符串大小，如果本身就符合条件就不用再赋值9
        for (int i = strNum.size() - 1; i > 0; i--)
        {
            if (strNum[i - 1] > strNum[i])
            {
                flag = i; // 用flag是为了防止1000这样的情况，如果是每次改成9，这里是900，但实际上是999
                strNum[i - 1]--;
            }
        }
        for (int i = flag; i < strNum.size(); i++)
        {
            strNum[i] = '9';
        }
        return stoi(strNum);
    }
};