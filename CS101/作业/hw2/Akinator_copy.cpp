#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;
long long result = 0;

struct Node
{
    bool IsCompound = false;
    long long f;
    Node *left;
    Node *right;
    Node() : IsCompound(false), f(0), left(nullptr), right(nullptr) {}
    Node(long long x) : IsCompound(false), f(x), left(nullptr), right(nullptr) {}
    Node(long long x, Node *left, Node *right) : IsCompound(false), f(x), left(left), right(right) {}
    bool operator>(const Node &other) const
    {
        return f > other.f; // Min-heap based on weight.
    }
};

struct CompareNode
{
    bool operator()(Node *l, Node *r)
    {
        return l->f > r->f; // Min-heap based on frequency.
    }
};

void countSum(Node *root, int height)
{
    if (root->left == nullptr && root->right == nullptr)
    {

        result += root->f * height;

        // cout << root->f << '*' << height;
        return;
    }
    countSum(root->left, height + 1);
    countSum(root->right, height + 1);
}

int main()
{

    int m;
    cin >> m;
    priority_queue<Node *, vector<Node *>, CompareNode> pq;
    map<long long, int> fmap;
    for (int i = 0; i < m; i++)
    {
        long long f;
        cin >> f;
        long long c;
        cin >> c;
        fmap[f] += c;
        if (c <= 2)
        {
            for (int j = 0; j < c; j++)
            {
                pq.push(new Node(f));
            }
        }
    }
    for (auto i = fmap.begin(); i != fmap.end(); i++)
    {

        if ((fmap[i->first] - 2) % 2 == 0)
        {
            for (int j = 0; j < 2; j++)
            {
                pq.push(new Node(i->first));
                fmap[i->first] -= 1;
            }
            fmap[2 * (i->first)] += fmap[i->first] / 2;

            result += (i->first) * fmap[i->first];
        }
        else if ((fmap[i->first] - 2) % 2 == 1)
        {
            pq.push(new Node(i->first));
            fmap[i->first] -= 1;
            fmap[2 * (i->first)] += fmap[i->first] / 2;
            result += (i->first) * fmap[i->first];
        }
    }

    while (pq.size() != 1) // 构造霍夫曼树
    {
        Node *left = pq.top();
        pq.pop();
        Node *right = pq.top();
        pq.pop();
        Node *top = new Node(left->f + right->f);
        top->left = left;
        top->right = right;
        pq.push(top);
    }

    countSum(pq.top(), 0);
    cout << result;
}
