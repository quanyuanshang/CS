#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
#include <climits>
#include <unordered_map>

const int MAX_VALUE = 100000;
using namespace std;

vector<pair<int, pair<int, int>>> adj[MAX_VALUE]; // 记录每个站点的公交线路和到下一站的时间
unordered_map<int, pair<int, int>> routes;        // 记录每条公交线路的发车时间和发车间隔
struct cmp
{
    bool operator()(pair<int, int> &a, pair<int, int> &b)
    {
        return a.second > b.second;
    }
};

int calculate_wait_time(int current_time, int travel_time, int first_departure, int interval)
{ // 这个条件只在人处在发车点有效。
    if (current_time < first_departure)
    {
        return first_departure - current_time; // 如果当前时间早于第一班车，等待第一班车
    }
    // 计算当前时间与发车间隔的模，确保等待时间正确
    int delta_time = (current_time - first_departure) % interval;

    cout << "current_time-first:" << current_time - first_departure << endl;
    cout << "delta_time:" << delta_time << endl;
    int wait_time;
    if (delta_time != 0)
    {
        wait_time = interval - delta_time; // 如果错过了上一班车，等待下一班车
    }
    else
    {
        wait_time = 0; // 如果当前时间正好是发车时间，不需要等待
    }
    return wait_time;
}

int find_earliest_arrival(int start, int end, int t0, vector<int> &visited)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;
    pq.push({start, t0}); // 起点站 S，起始时间为 t0

    while (!pq.empty())
    {
        int current_stop = pq.top().first;
        int current_time = pq.top().second;

        pq.pop();
        cout << "current_stop:" << current_stop << endl;
        cout << "current_time:" << current_time << endl;
        if (current_stop == end)
        {
            return current_time; // 如果到达终点站 T，返回当前时间
        }

        if (visited[current_stop] != 0 && visited[current_stop] <= current_time)
        {
            continue; // 如果当前站点已经被访问过，且到达时间不比之前记录的时间更早，跳过
        }

        visited[current_stop] = 1; // 更新当前站点的最早到达时间

        // 遍历从当前站点出发的所有公交线路
        for (auto &edge : adj[current_stop])
        {
            int travel_time = edge.first;
            cout << "travel_time:" << travel_time << endl;
            int route_id = edge.second.first;
            int next_stop = edge.second.second;

            // 获取当前线路的发车信息
            int first_departure = routes[route_id].first;
            int interval = routes[route_id].second;

            int wait_time = calculate_wait_time(current_time, travel_time, first_departure, interval);

            cout << "route:" << route_id << "wait_time:" << wait_time << endl;

            // 计算到达下一站的时间
            int arrival_time = current_time + wait_time + travel_time;
            cout << "arrival_time:" << arrival_time << endl;
            cout << "travel_time:" << travel_time << endl;

            // 将下一站和到达时间加入优先队列,排序之后就能pop出比较小的时间
            pq.push({next_stop, arrival_time + travel_time});
        }
    }

    return -1; // 如果无法到达终点站 T，返回 -1
}
int main()
{
    int n, m, t0, start_stop, end_stop;

    cin >> n >> m >> t0 >> start_stop >> end_stop;
    vector<int> visited(n + 1, 0);
    for (int i = 0; i < m; i++)
    {
        int l, f, d;
        cin >> l >> f >> d;
        vector<int> stops(l);
        vector<int> times(l);
        int cumulative_weight = 0;
        for (int &stop : stops)
            cin >> stop;
        for (int i = 1; i < l; i++)
        {
            cin >> times[i];
        } // 第一个站点是0.

        for (int j = 0; j < l; j++)
        {

            if (j != l - 1)
            {
                int u = stops[j], v = stops[j + 1];
                int travel_time = times[j];
                cumulative_weight += times[j];
                cout << "cumulative_weight:" << cumulative_weight << endl;
                adj[u].push_back({travel_time, {i, v}}); // 添加从 u 到 v 的公交线路
                cout << "adj[stop]:" << u << " corr route:" << i << "w:" << cumulative_weight << "next stop:" << v << endl;
            }
            else
            {
                int u = stops[j], v = -1;
                cumulative_weight += times[j];
                int travel_time = times[j];
                cout << "cumulative_weight:" << cumulative_weight << endl;
                adj[u].push_back({travel_time, {i, v}}); // 添加从 u 到 v 的公交线路
                cout << "adj[stop]:" << u << " corr route:" << i << "w:" << cumulative_weight << "next stop:" << v << endl;
            }
        }
        routes[i] = {f, d}; // 记录每条公交线路的发车时间和发车间隔
    }
    int earliest_arrival = find_earliest_arrival(start_stop, end_stop, t0, visited);
    cout << earliest_arrival << endl;
    return 0;
}