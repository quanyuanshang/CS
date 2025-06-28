#include <stack>
#include <queue>
#include <string>
#include <vector>
#include <deque>
#include <unordered_map>
#include <queue>
using namespace std;
/*template <typename T>
using stack = std::stack<T>;
template <typename T>
using queue = std::queue<T>;
using string = std::string;
template <typename T>
using vector = std::vector<T>;
template <typename T>
using deque = std::deque<T>;*/
// 用栈实现队列
class MyQueue
{
public:
    stack<int> stIn;
    stack<int> stOut;
    MyQueue()
    {
    }

    void push(int x)
    {
        stIn.push(x);
    }

    int pop()
    {
        if (stOut.empty())
        {
            while (!stIn.empty())
            {
                stOut.push(stIn.top());
                stIn.pop();
            }
        }
        int result = stOut.top();
        stOut.pop();
        return result;
    }

    int peek()
    {
        int res = this->pop();
        stOut.push(res);
        return res;
    }

    bool empty()
    {
        return stIn.empty() && stOut.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */

// 用队列实现栈
class MyStack
{
public:
    queue<int> que;
    MyStack()
    {
    }

    void push(int x)
    {
        que.push(x);
    }

    int pop()
    {
        int size = que.size();
        size--;

        while (size--)
        {
            que.push(que.front());
            que.pop();
        }
        int result = que.front();
        que.pop();
        return result;
    }

    int top()
    {
        return que.back();
    }

    bool empty()
    {
        return que.empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */

// 匹配括号
class Solution
{
public:
    bool isValid(string s)
    {
        stack<int> st;
        if (s.size() % 2 != 0)
            return false;
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == '(')
                st.push(')');
            else if (s[i] == '[')
                st.push(']');
            else if (s[i] == '{')
                st.push('}');
            else if (st.empty() || st.top() != s[i])
                return false;
            else
                st.pop();
        }
        return (st.empty());
    }
};

// 逆波兰表达式求值
class Solution
{
public:
    int evalRPN(vector<string> &tokens)
    {
        stack<int> st;
        for (int i = 0; i < tokens.size(); i++)
        {
            if (tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/")
            {
                int nums1 = st.top();
                st.pop();
                int nums2 = st.top();
                st.pop();
                if (tokens[i] == "+")
                {
                    st.push(nums2 + nums1);
                }
                if (tokens[i] == "-")
                {
                    st.push(nums2 - nums1);
                }
                if (tokens[i] == "/")
                {
                    st.push(nums2 / nums1);
                }
                if (tokens[i] == "*")
                {
                    st.push(nums2 * nums1);
                }
            }
            else
            {
                st.push(stoi(tokens[i]));
            }
        }
        int res = st.top();
        st.pop(); // 释放内存
        return res;
    }
};

// 滑动窗口最大值
class Solution
{
private:
    class Myqueue
    {
    public:
        deque<int> que;
        void pop(int val)
        {
            if (!que.empty() && val == que.front())
                que.pop_front();
        }
        void push(int val)
        {
            while (!que.empty() && val > que.back())
                que.pop_back();
            que.push_back(val);
        }
        int front()
        {
            return que.front();
        }
    };

public:
    vector<int>
    maxSlidingWindow(vector<int> &nums, int k)
    {
        Myqueue que;
        vector<int> result;
        for (int i = 0; i < k; i++)
        {
            que.push(nums[i]);
        }
        result.push_back(que.front());
        for (int i = k; i < nums.size(); i++)
        {
            que.pop(nums[i - k]); // 前一个窗口的首元素
            que.push(nums[i]);    // 后一个窗口的首元素
            result.push_back(que.front());
        }
        return result;
    }
};

// 求前k个高频元素
class Solution
{
public:
    class mycomparison
    {
    public:
        bool operator()(const pair<int, int> lhs, const pair<int, int> rhs)
        {
            return lhs.second > rhs.second;
        }
    };
    vector<int> topKFrequent(vector<int> &nums, int k)
    {
        unordered_map<int, int> map;
        for (int i = 0; i < nums.size(); i++)
        {
            map[nums[i]]++;
        }
        priority_queue<pair<int, int>, vector<pair<int, int>>, mycomparison> pri_que;
        for (unordered_map<int, int>::iterator it = map.begin(); it != map.end(); it++)
        {
            pri_que.push(*it);
            if (pri_que.size() > k)
            {
                pri_que.pop();
            }
        } // 每次让出现频次小的数出去
        // 倒序遍历输出
        vector<int> result(k);
        for (int i = k - 1; i >= 0; i--)
        {
            result[i] = pri_que.top().first;
            pri_que.pop();
        }

        return result;
    }
};