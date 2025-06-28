#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
inline int readint()
{
    int x;
    scanf("%d", &x);
    return x;
}
inline void writeint(long long x) { printf("%lld", x); }

struct Point
{
    int x, y; // 一个点
    Point(int X = 0, int Y = 0) : x(X), y(Y) {}
    void input() { x = readint(), y = readint(); }
    bool operator<(const Point &p) { return x < p.x; }
};

const int MaxN = 200005;
Point p[MaxN];
int n;

void input()
{
    n = readint();
    for (int i = 1; i <= n; ++i)
        p[i].input();
}

struct Stack
{ /* stupid Stack */
    int sta[MaxN], top;//用数组实现
    Stack() { top = 0; }
    void push_back(int x) { sta[++top] = x; }
    int back() const { return sta[top]; }
    bool empty() const { return top == 0; }
    int size() const { return top; }
    void pop_back()
    {
        if (top)
            --top;//实际上是没有删除，元素还在那里不过会被后面上来的元素替换
    }
    void clear() { top = 0; }
} lSta, rSta; /* y单减 */
int BadThing(int bound)
{ // 二分查找
    int L = 0, R = rSta.top, mid;
    while (L != R)
    {
        mid = (L + R + 1) >> 1;
        if (p[rSta.sta[mid]].y > bound)
            L = mid; /* 没有y值或x值相等的情况 */
        else
            R = mid - 1;
    }
    return L;
}

Point __tmp[MaxN];
long long ans;
void cdq(int left, int right)
{
    /* head: divide ... */
    if (left == right)
        return;
    int mid = (left + right) >> 1;
    cdq(left, mid), cdq(mid + 1, right);
    /* body: ... and conquer*/
    lSta.clear(), rSta.clear();//每个区间都单独计算
    for (int i = left, j = mid + 1; i <= mid; ++i)
    {
        for (; j <= right && p[j].y > p[i].y; ++j)//p[i]对A里的每个点选择
        {
            /* insert p[j] */
            while (!rSta.empty() && p[j].x < p[rSta.back()].x)
                rSta.pop_back(); // 维护x单增，一旦里面有点在它左下方，那么这个点不能要
            rSta.push_back(j);
        }
        /* find the "wall" */
        while (!lSta.empty() && p[lSta.back()].x < p[i].x)
            lSta.pop_back();//此时左边已经按照y递减，去求右上角中加入的最后一个元素
            //也就是要求栈里面大于p[i]x的那个元素
        /* update ans */
        ans += rSta.size();
        if (!lSta.empty())
            ans -= BadThing(p[lSta.back()].y);//B部分里面但凡有y比这个bound大，那么矩形里面一定有其他点。
        /* update lSta */
        lSta.push_back(i);
    }
    /* tail: sort it out */
    for (int i = left, j = mid + 1, k = left; k <= right; ++k)
        if (i <= mid && (j > right || p[i].y > p[j].y))
            __tmp[k] = p[i++];//维护y的降序，后入栈的点的y更小，那么维护栈就看x是不是也更小
        else
            __tmp[k] = p[j++];
    for (int i = left; i <= right; ++i)
        p[i] = __tmp[i];
}
void solve()
{
    /* 按照x值排序 ... */
    sort(p + 1, p + n + 1);
    /* ... 然后将y归并 */
    cdq(1, n); // 看着很短，不是吗？
    /* the most important part */
    writeint(ans), putchar('\n');
}

int main()
{
    input(), solve();
    return 0;
}

