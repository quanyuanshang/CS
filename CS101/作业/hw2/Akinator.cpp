#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
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
void SetCompound(Node *root)
{
    root->IsCompound = true;
}
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
        if (root->IsCompound == true)
        {
            result += root->f * (height + 1);
        }
        else
        {
            result += root->f * height;
        }

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
    for (int i = 0; i < m; i++)
    {
        long long f;
        cin >> f;
        int c;
        cin >> c;
        pq.push(new Node(f));
        c -= 1;
        while (c > 1)
        {
            Node *newnode = new Node(2 * f);
            pq.push(newnode);

            SetCompound(newnode);
            c -= 2;
        }
        if (c == 1)
        {
            pq.push(new Node(f));
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