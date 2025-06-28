#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
using string = std::string;
template <typename T>
using vector = std::vector<T>;
template <typename T>
using unordered_set = std::unordered_set<T>;
template <typename T>
using unordered_map = std::unordered_map<T>;
// 有效的字母异位词
class Solution
{
public:
    bool isAnagram(string s, string t)
    {
        int harsh[26] = {0};
        for (int i = 0; i < s.size(); i++)
        {
            harsh[s[i] - 'a']++;
        }
        for (int i = 0; i < t.size(); i++)
        {
            harsh[t[i] - 'a']--;
        }
        for (int i = 0; i < 26; i++)
        {
            if (harsh[i] != 0)
                return false;
        }
        return true;
    }
};

// 两个数组的交集
// 用set
class Solution
{
public:
    vector<int> intersection(vector<int> &nums1, vector<int> &nums2)
    {
        unordered_set<int> result;
        unordered_set<int> nums_set(nums1.begin(), nums1.end());
        for (int num : nums2)
        {
            if (nums_set.find(num) != nums_set.end())
            {
                result.insert(num);
            }
        }
        return vector<int>(result.begin(), result.end());
    }
};
// 用数组，有数据大小<1000的规定
class Solution
{
public:
    vector<int> intersection(vector<int> &nums1, vector<int> &nums2)
    {
        unordered_set<int> result;
        int harsh[1005] = {0};
        for (int i = 0; i < nums1.size(); i++)
        {
            harsh[nums1[i]] = 1; // 不用++防止重复
        }
        for (int i = 0; i < nums2.size(); i++)
        {
            if (harsh[nums2[i]] == 1)
            {
                result.insert(nums2[i]);
            }; // 不用++防止重复
        }

        return vector<int>(result.begin(), result.end());
    }
};

// 两数之和
class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        std::unordered_map<int, int> map;
        for (int i = 0; i < nums.size(); i++)
        {

            auto iter = map.find(target - nums[i]);
            if (iter != map.end())
            {
                return {iter->second, i};
            }
            map.insert(pair<int, int>(nums[i], i));
        }
        return {};
    }
};

// 四数相加
class Solution
{
public:
    int fourSumCount(vector<int> &nums1, vector<int> &nums2, vector<int> &nums3, vector<int> &nums4)
    {
        std::unordered_map<int, int> map;
        for (int a : nums1)
        {
            for (int b : nums2)
            {
                map[a + b]++;
            }
        }
        int count = 0;
        for (int c : nums3)
        {
            for (int d : nums4)
            {
                int target = 0 - (c + d);
                if (map.find(target) != map.end())
                {
                    count += map[target];
                }
            }
        }
        return count;
    }
};

// 三数之和
class Solution
{
public:
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] > 0) // 三元组里面最小的数都大于0了不行
                return result;
            // 三元素里面的值可以相等，找前面有没有相等的元素，前面相等说明前面和自己相等的这个首元素已经做好了找三元组的过程，这时候跳过没有问题
            if (i > 0 && nums[i] == nums[i - 1])
                continue;
            int left = i + 1;
            int right = nums.size() - 1;
            while (right > left) // 如果left right重复逻辑放在这里面可能直接导致right<=left从而漏掉{000}
            {
                if (nums[i] + nums[left] + nums[right] > 0)
                    right--;
                else if (nums[i] + nums[left] + nums[right] < 0)
                    left++;
                else
                    result.push_back(vector<int>{nums[i], nums[left], nums[right]});
                while (right > left && nums[right] == nums[right - 1])
                    right--;
                while (right > left && nums[left] == nums[left + 1])
                    left++;
                // 收获一个结果之后，双指针同时收缩
                left++;
                right--;
            }
        }
        return result;
    }
};

// 四数之和

class Solution
{
public:
    vector<vector<int>> fourSum(vector<int> &nums, int target)
    {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        for (int k = 0; k < nums.size(); k++)
        { // 剪枝
            if (nums[k] > target && nums[k] > 0 && target > 0)
            {
                break;
            }
            if (k > 0 && nums[k] == nums[k - 1])
                continue;
            for (int i = k + 1; i < nums.size(); i++)
            {
                if (i > k + 1 && nums[i] == nums[i - 1])
                    continue;
                int left = i + 1;
                int right = nums.size() - 1;
                while (right > left)
                {
                    if (nums[k] + nums[i] + nums[left] + nums[right] > target)
                        right--;
                    else if (nums[k] + nums[i] + nums[left] + nums[right] < target)
                        left++;
                    else
                    {
                        result.push_back(vector<int>{nums[k], nums[i], nums[left], nums[right]});
                        while (right > left && nums[right] == nums[right - 1])
                            right--;
                        while (right > left && nums[left] == nums[left + 1])
                            left++;
                        right--;
                        left++;
                    }
                }
            }
        }
        return result;
    }
};