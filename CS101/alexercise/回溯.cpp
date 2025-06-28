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
// 组合问题
class Solution
{
public:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(int n, int k, int startindex)
    {
        if (path.size() == k)
        {
            result.push_back(path);
            return;
        }
        for (int i = startindex; i <= n; i++)
        {
            path.push_back(i);
            backtracking(n, k, i + 1);
            path.pop_back();
        }
    }
    vector<vector<int>> combine(int n, int k)
    {
        result.clear();
        path.clear();
        backtracking(n, k, 1);
        return result;
    }
}; // 剪枝
class Solution
{
public:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(int n, int k, int startindex)
    {
        if (path.size() == k)
        {
            result.push_back(path);
            return;
        }
        for (int i = startindex; i <= n - (k - path.size()) + 1; i++)
        {

            path.push_back(i);
            backtracking(n, k, i + 1);
            path.pop_back();
        }
    }
    vector<vector<int>> combine(int n, int k)
    {
        result.clear();
        path.clear();
        backtracking(n, k, 1);
        return result;
    }
};
/// 组合3
class Solution
{
public:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(int targetSum, int k, int sum, int startindex)
    {
        if (sum > targetSum)
        {
            return;
        }

        if (path.size() == k)
        {
            if (targetSum == sum)
            {
                result.push_back(path);
            }

            return;
        }
        for (int i = startindex; i <= 10 - (k - path.size()); i++)
        {
            sum += i;
            path.push_back(i);
            backtracking(targetSum, k, sum, i + 1);
            sum -= i;
            path.pop_back();
        }
    }
    vector<vector<int>> combinationSum3(int k, int n)
    {
        backtracking(n, k, 0, 1);
        return result;
    }
};

// phone number
class Solution
{
public:
    const string letterMap[10] = {
        "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"} vector<string>;
    vector<string> result;
    string path;
    void backtracking(string &digits, int index, const string &path)
    {
        if (index == digits.size())
        {
            result.push_back(path);
            return;
        }
        int digit = digits[index] - '0';
        string letter = letterMap[digit];
        for (int i = 0; i < letter.size(); i++)
        {

            backtracking(digits, index + 1, path + letter[i]);
        }
    }
    vector<string> letterCombinations(string digits)
    {
        if (digits.size() == 0)
        {
            return result;
        }
        backtracking(digits, 0, "");
        return result;
    }
};
// 组合选取
class Solution
{
public:
    vector<vector<int>> result;
    vector<int> path;
    void backtracking(vector<int> &candidates, int k, int sum, int startindex)
    {
        if (sum > k)
        {
            return;
        }

        if (sum == k)
        {
            result.push_back(path);
            return;
        }
        for (int i = startindex; i < candidates.size() && sum + candidates[i] <= k; i++)
        { // 这要先对candidates进行排序，如果前面小的数的和都已经大于k了，那么后面一定都大于k了，直接结束循环。
            path.push_back(candidates[i]);
            sum += candidates[i];
            backtracking(candidates, k, sum, i);
            sum -= candidates[i];
            path.pop_back();
        }
    }
    vector<vector<int>> combinationSum(vector<int> &candidates, int target)
    {
        sort(candidates.begin(), candidates.end());
        backtracking(candidates, target, 0, 0);
    }
};

// 组合总和II,会出现重复元素
class Solution
{
public:
    vector<vector<int>> result;
    vector<int> path;

    void backtracking(vector<int> &candidates, int target, int startindex, int sum, vector<bool> &used)
    {
        if (sum > target)
        {
            return;
        }
        if (sum == target)
        {
            result.push_back(path);
            return;
        }
        for (int i = startindex; i < candidates.size() && sum + candidates[i] <= target; i++)
        {
            if (i > 0 && candidates[i] == candidates[i - 1] && used[i - 1] == false)
            {
                continue;
            }
            path.push_back(candidates[i]);
            sum += candidates[i];
            used[i] = true;
            backtracking(candidates, target, i + 1, sum, used);
            path.pop_back();
            sum -= candidates[i];
            used[i] = false;
        }
    }
    vector<vector<int>> combinationSum2(vector<int> &candidates, int target)
    {
        vector<bool> used(candidates.size(), false);
        sort(candidates.begin(), candidates.end());
        backtracking(candidates, target, 0, 0, used);
        return result;
    }
};

// 分割回文串
class Solution
{
public:
    vector<string> path;
    vector<vector<string>> result;
    bool isPalindrome(string &s, int startindex, int endindex)
    {
        for (int i = startindex, j = endindex; i < j; i++, j--)
        {
            if (s[i] != s[j])
            {
                return false;
            }
        }
        return true;
    }
    void backtracking(string &s, int startindex)
    {
        if (startindex >= s.size())
        {
            result.push_back(path);
            return;
        }
        for (int i = startindex; i < s.size(); i++)
        {
            if (isPalindrome(s, startindex, i))
            {
                string str = s.substr(startindex, i - startindex + 1);
                path.push_back(str);
            }
            else
            {
                continue;
            }
            backtracking(s, i + 1);
            path.pop_back();
        }
    }
    vector<vector<string>> partition(string s)
    {
        backtracking(s, 0);
        return result;
    }
};
// 复原IP地址
class Solution
{
public:
    vector<string> result;

    void backtracking(string &s, int startindex, int pointSum)
    {
        if (pointSum == 3)
        {
            if (IsValid(s, startindex, s.size() - 1))
            {
                result.push_back(s);
            }
            return;
        }
        for (int i = startindex; i < s.size(); i++)
        {
            if (IsValid(s, startindex, i))
            {
                s.insert(s.begin() + i + 1, '.');
                pointSum++;
                backtracking(s, i + 2, pointSum);
                pointSum--;
                s.erase(s.begin() + i + 1);
            }
            else
                break;
        }
    }
    bool IsValid(const string &s, int start, int end)
    {
        if (start > end)
        {
            return false;
        }
        if (s[start] == '0' && start != end)
        {
            return false;
        }
        int num = 0;
        for (int i = start; i <= end; i++)
        {
            if (s[i] > '9' || s[i] < '0') // 遇到非数字字符
            {
                return false;
            }
            num = num * 10 + (s[i] - '0'); // 从高位到低位求原数字
            if (num > 255)
            {
                return false;
            }
        }
        return true;
    }
    vector<string> restoreIpAddresses(string s)
    {
        result.clear();
        if (s.size() < 4 || s.size() > 12)
        {
            return result;
        }
        backtracking(s, 0, 0);
        return result;
    }
};
// 子集
class Solution
{
public:
    vector<int> path;
    vector<vector<int>> result;
    void backtracking(vector<int> &nums, int startindex)
    {
        result.push_back(path);
        if (startindex > nums.size() - 1)
        {
            return;
        }
        for (int i = startindex; i < nums.size(); i++)
        {
            path.push_back(nums[i]);
            backtracking(nums, i + 1);
            path.pop_back();
        }
    }
    vector<vector<int>> subsets(vector<int> &nums)
    {
        backtracking(nums, 0);
        return result;
    }
};
// 子集II
class Solution
{
public:
    vector<int> path;
    vector<vector<int>> result;
    void backtracking(vector<int> &nums, int startindex, vector<bool> used)
    {
        result.push_back(path);
        if (startindex > nums.size() - 1)
        {
            return;
        }
        for (int i = startindex; i < nums.size(); i++)
        {
            if (i > 0 && nums[i] == nums[i - 1] && used[i - 1] == false)
            {
                continue;
            }
            path.push_back(nums[i]);
            used[i] = true;
            backtracking(nums, i + 1, used);
            path.pop_back();
            used[i] = false;
        }
    }
    vector<vector<int>> subsetsWithDup(vector<int> &nums)
    {
        vector<bool> used(nums.size(), false);
        sort(nums.begin(), nums.end());
        backtracking(nums, 0, used);
        return result;
    }
};
// 递增子序列
class Solution
{
public:
    vector<int> path;
    vector<vector<int>> result;
    void backtracking(vector<int> &nums, int startindex)
    {
        if (path.size() > 1)
        {
            result.push_back(path);
        }
        unordered_set<int> uset; // 每一层都会创建记录使用情况的uset
        for (int i = startindex; i < nums.size(); i++)
        {
            if (!path.empty() && nums[i] < path.back() || uset.find(nums[i]) != uset.end())
            {
                continue;
            }

            path.push_back(nums[i]);
            uset.insert(nums[i]);
            backtracking(nums, i + 1);
            path.pop_back();
        }
    }
    vector<vector<int>> findSubsequences(vector<int> &nums)
    {
        backtracking(nums, 0);
        return result;
    }
};
// 排列问题
class Solution
{
public:
    vector<int> path;
    vector<vector<int>> result;
    void backtracking(vector<int> &nums, vector<bool> &used)
    {
        if (path.size() == nums.size())
        {
            result.push_back(path);
            return;
        }
        for (int i = 0; i < nums.size(); i++)
        {
            if (used[i] == true)
            {
                continue;
            }
            path.push_back(nums[i]);
            used[i] = true;
            backtracking(nums, used);
            path.pop_back();
            used[i] = false;
        }
    }
    vector<vector<int>> permute(vector<int> &nums)
    {
        vector<bool> used(nums.size(), false);
        backtracking(nums, used);
        return result;
    }
};
// 排列
class Solution
{
public:
    vector<int> path;
    vector<vector<int>> result;
    void backtracking(vector<int> &nums, vector<bool> &used)
    {
        if (path.size() == nums.size())
        {
            result.push_back(path);
            return;
        }
        for (int i = 0; i < nums.size(); i++)
        {
            if (i > 0 && nums[i - 1] == nums[i] && used[i - 1] == false)
            {
                continue;
            }
            if (used[i] == true)
            {
                continue;
            }
            path.push_back(nums[i]);
            used[i] = true;
            backtracking(nums, used);
            path.pop_back();
            used[i] = false;
        }
    }

    vector<vector<int>> permuteUnique(vector<int> &nums)
    {
        vector<bool> used(nums.size(), false);
        sort(nums.begin(), nums.end());
        backtracking(nums, used);
        return result;
    }
};

// N-queen
class Solution
{
public:
    vector<vector<string>> result;
    void backtracking(int n, int row, vector<string> &chessboard)
    {
        if (row == n)
        {
            result.push_back(chessboard);
            return;
        }
        for (int i = 0; i < n; i++)
        {
            if (IsValid(row, i, chessboard, n))
            {
                chessboard[row][i] = 'Q';
                backtracking(n, row + 1, chessboard);
                chessboard[row][i] = '.';
            }
        }
    }
    bool IsValid(int row, int col, vector<string> &chessboard, int n)
    {
        for (int i = 0; i < row; i++)
        {
            if (chessboard[i][col] == 'Q')
            {
                return false;
            }
        }
        for (int i = 0; i < col; i++)
        {
            if (chessboard[row][i] == 'Q')
            {
                return false;
            }
        }
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
        {
            if (chessboard[i][j] == 'Q')
            {
                return false;
            }
        }
        for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++)
        {
            if (chessboard[i][j] == 'Q')
            {
                return false;
            }
        }
        return true;
    }
    vector<vector<string>> solveNQueens(int n)
    {
        vector<string> chessboard(n, string(n, '.'));
        backtracking(n, 0, chessboard);
        return result;
    }
};
// 解数独
class Solution
{
public:
    bool backtracking(vector<vector<char>> &board)
    {
        for (int i = 0; i < board.size(); i++) // 行
        {
            for (int j = 0; j < board[0].size(); j++) // 列
            {
                if (board[i][j] != '.')
                {
                    continue;
                }
                for (char k = '1'; k <= '9'; k++)
                {
                    if (isValid(i, j, k, board))
                    {
                        board[i][j] = k;
                        bool result = backtracking(board);
                        if (result == true)
                        {
                            return true;
                        }
                        board[i][j] = '.';
                    }
                }
                return false;
            }
        }
        return true;
    }
    bool isValid(int row, int col, char val, vector<vector<char>> &board)
    {
        for (int i = 0; i < 9; i++)
        {
            if (board[row][i] == val)
            {
                return false;
            }
        }
        for (int j = 0; j < 9; j++)
        {
            if (board[j][col] == val)
            {
                return false;
            }
        }
        int startRow = (row / 3) * 3;
        int startCol = (col / 3) * 3;
        for (int i = startRow; i < startRow + 3; i++)
        {
            for (int j = startCol; j < startCol + 3; j++)
            {
                if (board[i][j] == val)
                {
                    return false;
                }
            }
        }
        return true;
    }
    void solveSudoku(vector<vector<char>> &board)
    {
        backtracking(board);
    }
};