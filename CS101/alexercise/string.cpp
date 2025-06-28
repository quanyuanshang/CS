#include <string>
#include <vector>
#include <utility>
#include <algorithm>
template <typename T>
using vector = std::vector<T>;
using string = std::string;

class Solution
{
public:
    void reverseString(vector<char> &s)
    {
        int len = s.size();
        for (int i = 0, j = len - 1; i < len / 2; i++, j--)
        {
            std::swap(s[i], s[j]);
        }
    }
};

class Solution
{
public:
    string reverseStr(string s, int k)
    {
        for (int i = 0; i < s.size(); i += 2 * k)
        {
            if (i + k <= s.size())

            {
                std::reverse(s.begin() + i, s.begin() + i + k); // 左闭右开
                continue;
            }
            std::reverse(s.begin() + i, s.begin() + s.size());
        }
        return s;
    }
};

// 反转字符串里的单词
class Solution
{
public:
    void removeextra(string &s)
    {
        int slow = 0;
        int fast = 0;
        while (s.size() > 0 && fast < s.size() && s[fast] == ' ')
        {
            fast++;
        } // 去掉字符串前面的空格

        for (; fast < s.size(); fast++) // 此时一定是进入了第一个字母
        {
            if (fast - 1 > 0 && s[fast - 1] == s[fast] && s[fast] == ' ')
            {
                continue; // 去除中间冗余空格
            }
            else
            {
                s[slow] = s[fast];
                slow++;
            }

        } // 去除结尾的空格
        if (slow - 1 > 0 && s[slow - 1] == ' ')
        {
            s.resize(slow - 1);
        }
        else
        {
            s.resize(slow);
        }
    }
    void reverse(string &s, int start, int end)
    {
        for (int i = start, j = end; i < j; i++, j--)
        {
            std::swap(s[i], s[j]);
        }
    }
    string reverseWords(string s)
    {
        removeextra(s);
        reverse(s, 0, s.size() - 1);
        int start = 0;
        int end = 0;
        bool entry = false; // 是否进入了单词。
        for (int i = 0; i < s.size(); i++)
        {
            if (!entry || (s[i] != ' ' && s[i - 1] == ' '))
            {
                start = i;
                entry = true;
            }
            if (entry && s[i] == ' ' && s[i - 1] != ' ')
            {
                end = i - 1;
                entry = false;
                reverse(s, start, end);

            } // 最后一个单词
            if (entry && (i == (s.size() - 1)) && s[i] != ' ')
            {
                end = i;
                entry = false;
                reverse(s, start, end);
            }
        }
        return s;
    }
};

// 找到重复的子字符串
// 移动匹配
class Solution
{
public:
    void getNext(int *next, const string &s)
    {
        next[0] = 0;
        int j = 0;
        for (int i = 1; i < s.size(); i++)
        {
            while (j > 0 && s[i] != s[j])
            {
                j = next[j - 1];
            }
            if (s[i] == s[j])
            {
                j++;
            }
            next[i] = j;
        }
    }
    bool repeatedSubstringPattern(string s)
    {

        if (s.size() == 0)
        {
            return false;

            int next[s.size()];
            getNext(next, s);
            int len = s.size();
            if (next[len - 1] != 0 && len % (len - (next[len - 1])) == 0)
                return true;
        }
        return false;
    }
};

// str（）
class Solution
{
public:
    void getNext(int *next, const string &s)
    { // 后缀表建立
        next[0] = 0;
        int j = 0;
        for (int i = 1; i < s.size(); i++)
        {
            while (j > 0 && s[i] != s[j])
            {
                j = next[j - 1];
            }
            if (s[i] == s[j])
            {
                j++;
            }
            next[i] = j;
        }
    }
    int strStr(string haystack, std::string needle)
    {
        if (needle.size() == 0)
        {
            return false;
        }
        int next[needle.size()];
        getNext(next, needle);
        int j = 0;
        for (int i = 0; i < haystack.size(); i++)
        {
            while (j > 0 && haystack[i] != needle[j])
            {
                j = next[j - 1];
            }
            if (haystack[i] == needle[j])
                j++;
            if (j == needle.size())
                return (i - needle.size() + 1);
            return -1;
        }
    }
};