#include <algorithm>
#include <cstdio>
#include <climits>

// The struct for nodes in AVL.
struct Node
{
    int size, height;
    int s, sum;
    Node *parent, *child[2];
    Node() : size(0), height(0), s(0), sum(0), parent(nullptr), child{nullptr, nullptr} {}
    Node(int val) : size(1), height(0), s(val), sum(val), parent(nullptr), child{&dummy, &dummy} {}
    ~Node();
};

Node dummy(0); // Global dummy node

// Node destructor.
Node::~Node()
{
    if (this == &dummy)
        return;
    if (child[0] && child[0] != &dummy)
        delete child[0];
    if (child[1] && child[1] != &dummy)
        delete child[1];
}

// The struct for an AVL tree.
struct Tree
{
    Node *root;
    Tree() : root(&dummy) {}
    ~Tree()
    {
        if (root != &dummy)
            delete root;
    }
} tree;

// Update size, height and sum of node u.
void update(Node *u)
{
    u->size = 1 + u->child[0]->size + u->child[1]->size;
    u->height = 1 + std::max(u->child[0]->height, u->child[1]->height);
    u->sum = u->s + u->child[0]->sum + u->child[1]->sum;
}

// Perform a single rotation on node u.
void rotate(Node *u)
{
    Node *p = u->parent;
    bool isLeftChild = (u == p->child[0]);
    Node *v = u->child[!isLeftChild];
    u->child[!isLeftChild] = v->child[isLeftChild];
    if (v->child[isLeftChild] != &dummy)
    {
        v->child[isLeftChild]->parent = u;
    }
    v->child[isLeftChild] = u;
    u->parent = v;
    v->parent = p;
    if (p != &dummy)
    {
        p->child[p->child[1] == u] = v;
    }
    else
    {
        tree.root = v;
    }
    update(u);
    update(v);
}

// Check and correct imbalances from u to root.
void update_and_balance(Node *u)
{
    while (u != &dummy)
    {
        update(u);
        int balance = u->child[0]->height - u->child[1]->height;
        if (balance > 1)
        {
            if (u->child[0]->child[0]->height < u->child[0]->child[1]->height)
                rotate(u->child[0]);
            rotate(u);
        }
        else if (balance < -1)
        {
            if (u->child[1]->child[1]->height < u->child[1]->child[0]->height)
                rotate(u->child[1]);
            rotate(u);
        }
        u = u->parent;
    }
}

// Subtask 1: Insert x into the AVL, and maintain the balance.
void insert(int x)
{
    Node *p = &dummy;
    Node *u = tree.root;
    while (u != &dummy)
    {
        p = u;
        if (x <= u->s)
            u = u->child[0];
        else
            u = u->child[1];
    }
    u = new Node(x);
    u->parent = p;
    if (p != &dummy)
    {
        if (x <= p->s)
            p->child[0] = u;
        else
            p->child[1] = u;
    }
    else
    {
        tree.root = u;
    }
    update_and_balance(p);
}

// Subtask 2: Find x in the AVL.
Node *find(int x)
{
    Node *u = tree.root;
    while (u != &dummy)
    {
        if (x == u->s)
        {
            return u;
        }
        u = u->child[x > u->s];
    }
    return &dummy;
}

// Subtask 3: Erase x from the AVL, and maintain the balance.
void erase(int x)
{
    Node *u = find(x);
    if (u == &dummy)
    {
        return;
    }
    if (u->child[0] == &dummy)
    {
        u = u->child[1];
    }
    else if (u->child[1] == &dummy)
    {
        u = u->child[0];
    }
    else
    {
        Node *v = u->child[1];
        while (v->child[0] != &dummy)
        {
            v = v->child[0];
        }
        u->s = v->s;
        u = v;
    }
    Node *p = u->parent;
    Node *v = u->child[u->child[0] == &dummy];
    if (v != &dummy)
    { 
        v->parent = p;
    }
    if (p != &dummy)
    {
        p->child[p->child[1] == u] = v;
    }
    else
    {
        tree.root = v;
    }
    delete u;
    update_and_balance(p);
}

// Subtask 4: Query the k-th node in the AVL.
int kth(int k)
{
    Node *u = tree.root;
    while (u != &dummy)
    {
        int leftSize = u->child[0]->size;
        if (k <= leftSize)
        {
            u = u->child[0];
        }
        else if (k == leftSize + 1)
        {
            return u->s;
        }
        else
        {
            k -= leftSize + 1;
            u = u->child[1];
        }
    }
    return -1;
}

// Subtask 5: Return the minimum ans, as described in problem statement.
int ans(int k)
{
    Node *u = tree.root;
    int total = u->sum;
    int prefix = 0, minAns = INT_MAX;
    while (u != &dummy)
    {
        int leftSum = prefix + u->child[0]->sum + u->s;
        int rightSum = total - leftSum;
        int diff = k * leftSum - rightSum;
        if (diff >= 0)
        {
            minAns = std::min(minAns, diff);
            u = u->child[0];
        }
        else
        {
            prefix = leftSum;
            u = u->child[1];
        }
    }
    return minAns;
}

// Print the pre-order of AVL to check whether you maintain the tree structure correctly.
void preorder(Node *u)
{
    if (u == &dummy)
        return;
    printf("%d %d %d\n", u->s, u->height, u->sum);
    preorder(u->child[0]);
    preorder(u->child[1]);
}

// YOU DON'T NEED AND SHOULD NOT MODIFY main()!
int main()
{
#ifndef ONLINE_JUDGE
    freopen("avl.in", "r", stdin);
    freopen("avl.out", "w", stdout);
#endif
    int n, opt, x;
    Node *u;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d %d", &opt, &x);
        printf("----------#%d: %d %d----------\n", i, opt, x);
        switch (opt)
        {
        case 1:
            insert(x);
            preorder(tree.root);
            break;
        case 2:
            u = find(x);
            if (u == &dummy)
                printf("Not found!\n");
            else
                printf("%d\n", u->height);
            break;
        case 3:
            erase(x);
            preorder(tree.root);
            break;
        case 4:
            if (x < 1 || x > tree.root->size)
                printf("Invalid query!\n");
            else
                printf("%d\n", kth(x));
            break;
        case 5:
            if (tree.root->size == 0)
                printf("Invalid query!\n");
            else
                printf("%d\n", ans(x));
        }
    }
    return 0;
}