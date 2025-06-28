#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;
const int mod = 1e9 + 7;
const int BOUND = 2000000;
int main()
{
    long long s, t, k, m;
    long long tot = 0;
    long long tot_no = 0;
    scanf("%lld %lld %lld %lld", &s, &t, &k, &m);
    vector<int> a(m);
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &a[i]);
    }
    if (k == 1)
    {
        if (s != t)
        {
            printf("0\n");
            return 0;
        }
        else
        {
            printf("1\n");
            for (int i = 0; i < m; i++)
            {
                printf("%lld ", s);
            }

            return 0;
        }
    }
    vector<vector<long long>> dp(k + 1, vector<long long>(10, 0));
    vector<vector<long long>> dp_no(k + 1, vector<long long>(10, 0));
    for (int i = 0; i < 10; i++) // 初始化
    {
        if (i == t)
        {
            dp[0][i] = 1;
            dp_no[0][i] = 1;
        }
        else
        {
            dp[0][i] = 0;
            dp_no[0][i] = 0;
        }
    }
    if (k >= 2)
    {
        for (int step = 1; step < k; step++) // 计算总数
        {
            for (int i = 0; i < 10; i++)
            {
                if (i > 0)
                {
                    dp[step][i] += dp[step - 1][i - 1];
                    dp_no[step][i] += dp_no[step - 1][i - 1];
                }
                if (i < 9)
                {
                    dp[step][i] += dp[step - 1][i + 1];
                    dp_no[step][i] += dp_no[step - 1][i + 1];
                }
                dp[step][i] %= mod;
                if (dp_no[step][i] > BOUND)
                {
                    dp_no[step][i] = BOUND;
                }
            }
        }
        tot = dp[k - 1][s];
        tot_no = dp_no[k - 1][s];
        printf("%lld\n", tot);
        // printf("%lld\n", tot_no);
    }
    for (auto &rank : a) // 输出第rank个数
    {
        if (rank > tot_no)
        {
            cout << -1 << endl;
            continue;
        }

        string number;
        number.push_back(s + '0');
        int current = s;
        int step = 1;
        while (step < k)
        {

            for (int next = current - 1; next <= current + 1; next += 2)
            {
                if (next < 0 || next > 9)
                    continue;
                long long count = dp_no[k - step][next];
                if (count < rank)
                {
                    rank -= count;
                }
                else
                {
                    number.push_back(next + '0');
                    current = next;
                    break;
                }
            }

            step += 1;
        }
        number.push_back(t + '0');
        cout << number << "\n";
    }
}
