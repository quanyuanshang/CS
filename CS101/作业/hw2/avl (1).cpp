#include <algorithm>
#include <cstdio>

// The struct for nodes in AVL.
struct Node
{
    int size, height;
    int s, sum;
    Node *parent, *child[2];
    ~Node();
} dummy{0, -1, 0, 0, nullptr, nullptr, nullptr};

// We can handle fewer boundary conditions if we implement AVL with a dummy node.
Node *dummyptr = &dummy;

// Node destructor.
Node::~Node()
{
    if (this == dummyptr)
        return;
    if (child[0] != dummyptr)
        delete child[0];
    if (child[1] != dummyptr)
        delete child[1];
}

// The struct for an AVL tree.
struct Tree
{
    Node *root;
    ~Tree()
    {
        if (root != dummyptr)
            delete root;
    }
} tree{dummyptr};

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
    Node *v = u->child[isLeftChild];
    u->child[isLeftChild] = v->child[!isLeftChild];
    if (v->child[isLeftChild] != dummyptr)
    {
        v->child[isLeftChild]->parent = u;
    }
    v->child[!isLeftChild] = u;
    u->parent = v;
    v->parent = p;
    if (p != dummyptr)
    {
        p->child[isLeftChild] = v;
    }
    else
    {
        tree.root = v;
    }
    update(u);
    update(v);
}

// Check and correct imbalances from u to root.
// If an imbalance is Case 1 (LL or RR), Perform the single rotation once.
// If an imbalance is Case 2 (LR or RL), Perform the single rotation twice.
// If an imbalance is Case 3 (L- or R-), Perform the single rotation once.
void update_and_balance(Node *u)
{
    while (u != dummyptr)
    {
        update(u);
        int balance = u->child[0]->height - u->child[1]->height;
        if (balance > 1)
        {
            if (u->child[0]->child[0]->height < u->child[0]->child[1]->height)
            {
                rotate(u->child[0]); // 把左孩子放到中间，再把自己放到中间
            }
            rotate(u);
        }
        else if (balance < -1)
        {
            if (u->child[1]->child[1]->height < u->child[1]->child[0]->height)
            {
                rotate(u->child[1]);
            }
            rotate(u);
        }
        u = u->parent;
    }
}

// Subtask 1: Insert x into the AVL, and maintain the balance.
// Insertion is stable. In other words, the last inserted node should be the last node in in-order traversal among those who have the same value.
void insert(int x)
{
    Node *p = dummyptr;
    Node *u = tree.root;
    while (u != dummyptr)
    {
        p = u;
        u = u->child[x >= u->s];
    }
    u = new Node{x, 1, 1, x, p, {dummyptr, dummyptr}};
    if (p != dummyptr)
    {
        p->child[x >= p->s] = u;
    }
    else
    {
        tree.root = u;
    }
    update_and_balance(p);
}

// Subtask 2: Find x in the AVL.
// If x not found, return dummyptr.
// If there are multiple nodes with node.s==x, return the node with the smallest depth.
Node *find(int x)
{
    Node *u = tree.root;
    while (u != dummyptr)
    {
        if (x == u->s)
        {
            return u;
        }
        u = u->child[x > u->s];
    }
    return dummyptr;
}

// Subtask 3: Erase x from the AVL, and maintain the balance.
// If x not found, just do nothing and return.
// If there are multiple nodes with node.s==x, erase the node with the smallest depth.
// If the erased node has two children, replace it with the first node of in-order traversal of its right subtree.
void erase(int x)
{
    Node *u = find(x);
    if (u == dummyptr)
    {
        return;
    }
    if (u->child[0] == nullptr)
    {
        u = u->child[1];
    }
    else if (u->child[1] == nullptr)
    {
        u = u->child[0];
    }
    else if (u->child[0] != dummyptr && u->child[1] != dummyptr)
    {
        Node *v = u->child[1];
        while (v->child[0] != dummyptr)
        {
            v = v->child[0];
        }
        u->s = v->s;
        u = v;
    }
    Node *p = u->parent;
    Node *v = u->child[u->child[0] == dummyptr];
    if (v != dummyptr)
    { // 非空的左孩子/可能是空的有孩子
        v->parent = p;
    }
    if (p != dummyptr)
    {
        p->child[p->child[1] == u] = v; // child[0];
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
    while (u != dummyptr)
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
    int total = tree.root->sum;
    int prefix = 0, res = 1e9;
    while (u != dummyptr)
    {
        int leftSum = prefix + u->child[0]->sum + u->s;
        int rightSum = total - leftSum;
        int diff = k * leftSum - rightSum;
        if (diff >= 0)
        {
            res = std::min(res, diff);
            u = u->child[0];
        }
        else
        {
            prefix += u->child[0]->sum + u->s;
            u = u->child[1];
        }
    }
    return res;
}

// Print the pre-order of AVL to check whether you maintain the tree structure correctly.
void preorder(Node *u)
{
    if (u == dummyptr)
        return;
    printf("%d %d %d %d\n", u->s, u->parent->s, u->child[0]->s, u->child[1]->s);
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
    int n, opt;
    int x;
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
            if (u == dummyptr)
                printf("Not found!\n");
            else
                printf("%d\n", u->height);
            break;
        case 3:
            erase(x);
            preorder(tree.root);
            break;
        case 4:
            if (x < 1 or x > tree.root->size)
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
