#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int n, W, k; // n: number of equipment, W: capacity, k: mission number
struct eqp
{
    int l, w, v; // l: limit, w: weight, v: value
    eqp(int _l, int _w, int _v)
        : l(_l), w(_w), v(_v) {}
};
vector<eqp> equipment;

/*
You can share a public variable(function) sets since only 1 mission will be executed once.
*/

// MISSION1: all equipment with l = -1
int Mission1()
{
    vector<int> dp(W + 1, 0);
    int ans = 0;
    for (std::vector<eqp>::size_type i = 0; i < equipment.size(); i++)
        for (int j = equipment[i].w; j <= W; j++)
            dp[j] = max(dp[j], dp[j - equipment[i].w] + equipment[i].v);

    ans = dp[W];

    return ans;
}

// MISSION2: all equipment with l = 1
int Mission2()
{
    vector<int> dp(W + 1, 0);
    int ans = 0;
    // TODO: Finish Mission 2.
    for (std::vector<eqp>::size_type i = 0; i < equipment.size(); i++)
        for (int j = W; j >= equipment[i].w; j--)
            dp[j] = max(dp[j], dp[j - equipment[i].w] + equipment[i].v);

    ans = dp[W];
    return ans;
}

// MISSION3: Liquid tanks: Can bring any fractional unit of liquid, w|v
int Mission3()
{
    int ans = 0;
    // TODO: Finish Mission 3.

    sort(equipment.begin(), equipment.end(), [](const eqp &a, const eqp &b)
         { return a.v * b.w > b.v * a.w; });
    for (auto &e : equipment)
    {

        if (W == 0)
        {
            break;
        }

        if (e.l == -1)
        {
            while (e.w < W)
            {
                ans += e.v;
                W -= e.w;
            }

            double frac = double(W) / e.w;
            ans += frac * e.v;
            W = 0;
        }
        else
        {
            while (e.w < W && e.l != 0)
            {
                ans += e.v;
                // cout << ans << "  w<W" << endl;
                W -= e.w;
                // cout << W << "  w<W" << endl;
                e.l--;
            }
            if (e.l != 0)
            {
                // cout << "here" << endl;
                double frac = double(W) / e.w;
                // cout << frac << "  frac" << endl;
                ans += frac * e.v;
                W = 0;
            }
        }
    }
    return ans;
}

// Input Part, you can modify this.
void getInput()
{
    scanf("%d%d%d", &k, &n, &W);
    for (int i = 1; i <= n; ++i)
    {
        int l, w, v;
        scanf("%d%d%d", &l, &w, &v);
        equipment.emplace_back(l, w, v);
    }
}

// You'd better not to modify things below.
int (*MISSION_FUNC[])() = {nullptr, Mission1, Mission2, Mission3};

int main()
{
    getInput();
    int ans = MISSION_FUNC[k]();
    std::cout << ans;
    return 0;
}