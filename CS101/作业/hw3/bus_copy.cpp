#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
#include <climits>
#include <unordered_map>

const int MAX_VALUE = 100000; // This constant is no longer needed
using namespace std;

struct Edge
{
    int route_id;
    int next_stop;
    long long travel_time;
    long long accumulative_time;
    long long interval;
    long long first_departure;
    Edge(int route_id, int next_stop, long long travel_time, long long accumulative_time, long long interval, long long first)
        : route_id(route_id), next_stop(next_stop), travel_time(travel_time), accumulative_time(accumulative_time), interval(interval), first_departure(first) {}
    Edge() : route_id(0), next_stop(0), travel_time(0), accumulative_time(0), interval(0), first_departure(0) {}
};

unordered_map<int, vector<Edge>> adj; // 记录每个站点的公交线路和到下一站的时间

struct cmp
{
    bool operator()(pair<int, long long> &a, pair<int, long long> &b)
    {
        return a.second > b.second;
    }
};

long long calculate_wait_time(long long current_time, long long first_departure, long long interval, long long accumulative_time)
{
    long long departure_time = first_departure + accumulative_time;
    if (current_time < first_departure + accumulative_time)
    {
        return departure_time; // 如果当前时间早于第一班车，等待第一班车
    }
    long long wait = (current_time - departure_time + interval - 1) / interval;
    return wait * interval + departure_time;
}

long long find_earliest_arrival(int start, int end, long long t0, vector<long long> &visited)
{
    priority_queue<pair<int, long long>, vector<pair<int, long long>>, cmp> pq;
    pq.push({start, t0}); // 起点站 S，起始时间为 t0

    while (!pq.empty())
    {
        int current_stop = pq.top().first;
        long long current_time = pq.top().second;
        pq.pop();

        if (current_stop == end)
        {
            return current_time; // 如果到达终点站 T，返回当前时间
        }

        if (visited[current_stop] != LLONG_MAX && visited[current_stop] <= current_time)
        {
            continue; // 如果当前站点已经被访问过，且到达时间不比之前记录的时间更早，跳过
        }

        visited[current_stop] = current_time; // 更新当前站点的最早到达时间

        // 遍历从当前站点出发的所有公交线路
        for (auto &edge : adj[current_stop])
        {
            long long travel_time = edge.travel_time;
            long long accumulative_time = edge.accumulative_time;
            int next_stop = edge.next_stop;
            long long first_departure = edge.first_departure;
            long long interval = edge.interval;
            long long arrival_time = calculate_wait_time(current_time, first_departure, interval, accumulative_time);

            if (next_stop == -1)
            {
                continue;
            }
            else
            {
                pq.push({next_stop, arrival_time + travel_time});
            }
        }
    }

    return -1; // 如果无法到达终点站 T，返回 -1
}

int main()
{
    int n, m, start_stop, end_stop;
    long long t0;

    cin >> n >> m >> t0 >> start_stop >> end_stop;
    vector<long long> visited(n + 1, LLONG_MAX);
    for (int i = 0; i < m; i++)
    {
        int l;
        long long f, d;
        cin >> l >> f >> d;
        vector<int> stops(l);
        vector<long long> times(l, 0);
        long long accumulative_weight = 0;
        for (int &stop : stops)
            cin >> stop;
        for (int i = 1; i < l; i++)
        {
            cin >> times[i];
        }

        for (int j = 0; j < l; j++)
        {
            int u = stops[j];
            int v = j == l - 1 ? -1 : stops[j + 1];
            long long travel_time = j == l - 1 ? -1 : times[j + 1];
            accumulative_weight += times[j];

            adj[u].push_back(Edge(i, v, travel_time, accumulative_weight, d, f)); // 添加从 u 到 v 的公交线路
        }
    }

    long long earliest_arrival = find_earliest_arrival(start_stop, end_stop, t0, visited);
    cout << earliest_arrival << endl;
    return 0;
}
