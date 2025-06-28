#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge
{
    int u, v, w, s;
    Edge(int u = 0, int v = 0, int w = 0, int s = 0) : u(u), v(v), w(w), s(s) {}
    bool operator<(const Edge &other) const
    {
        if (w == other.w)
        {
            return s > other.s;
        }
        return w < other.w;
    }
};

vector<Edge> edges;
vector<int> parent;
int total_weight = 0, special_count = 0;
int m;

int find(int u)
{
    if (u != parent[u])
    {
        parent[u] = find(parent[u]);
    }
    return parent[u];
}

void kruskal(int n, int mid)
{
    total_weight = 0;
    special_count = 0;
    parent.resize(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        parent[i] = i;
    }
    for (auto &edge : edges)
    {
        if (edge.s == 1)
        {
            edge.w += mid;
        }
    }
    sort(edges.begin(), edges.end());
    int edge_count = 0;
    for (const auto &edge : edges)
    {
        int u_root = find(edge.u);
        int v_root = find(edge.v);
        if (u_root != v_root)
        {
            parent[u_root] = v_root;
            total_weight += edge.w;
            special_count += edge.s;
            edge_count++;
            if (edge_count == n - 1)
            {
                break;
            }
        }
    }
    for (auto &edge : edges)
    {
        if (edge.s == 1)
        {
            edge.w -= mid;
        }
    }
}

int main()
{
    int n, k;
    cin >> n >> m >> k;
    edges.resize(m);
    for (int i = 0; i < m; ++i)
    {
        int u, v, w, s;
        cin >> u >> v >> w >> s;
        edges[i] = Edge(u, v, w, s);
    }

    int left = -100000, right = 100000;
    int result = 0;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        kruskal(n, mid);
        if (special_count < k)
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
            result = total_weight - k * mid;
        }
    }

    cout << result << endl;
    return 0;
}
