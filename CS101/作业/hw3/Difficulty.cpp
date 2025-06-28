#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;
    vector<int> Qd(n);
    vector<int> Ta(n);
    for (int i = 0; i < n; i++)
    {
        cin >> Qd[i];
        // cout << "a_i:" << Qd[i] << endl;
    }
    for (int i = 0; i < n; i++)
    {
        cin >> Ta[i];
        // cout << "b_i:" << Ta[i] << endl;
    }
    sort(Ta.begin(), Ta.end());
    vector<int> count(n, 0);
    for (int i = 0; i < n; i++) // 被多少个长度为k的连续子序列覆盖
    {
        int left = max(0, i - k + 1); // 在子序列里所能到的最左的位置
        int right = min(i, n - k);    // 在子序列里所能到的最右的位置
        count[i] = right - left + 1;
        // cout << "count:" << i << ":" << count[i] << endl;
    }
    vector<long long> weight(n, 0);
    for (int i = 0; i < n; i++)
    {
        weight[i] = count[i] * Qd[i];
        // cout << "weight:" << i << ":" << weight[i] << endl;
    }
    sort(weight.begin(), weight.end());
    long long sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += weight[i] * Ta[n - 1 - i];
        // cout << "weight:" << weight[i] << endl;
        // cout << "Ta:" << Ta[n - 1 - i] << endl;
        // cout << "sum:" << sum << endl;
    }
    cout << sum << endl;
}