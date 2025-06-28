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
    Node *g = p->parent;
    bool UisRightChild = (u == p->child[1]);
    bool PisRightChild = (g != dummyptr) ? (p == g->child[1]) : false;
    Node *c = u->child[!UisRightChild];
    u->parent = g;
    if (g != dummyptr)
    {
        g->child[PisRightChild] = u;
    }
    else
    {
        tree.root = u;
    }
    p->child[UisRightChild] = c;
    if (c != dummyptr)
    {
        c->parent = p;
    }
    u->child[!UisRightChild] = p;
    p->parent = u;
    update(p);
    update(u);
}
void update_and_balance(Node *u)
{
    while (u != dummyptr)
    {
        update(u);
        int balance = u->child[0]->height - u->child[1]->height;
        if (balance > 1)
        {
            if (u->child[0]->child[0]->height >= u->child[0]->child[1]->height)
                rotate(u->child[0]);
            else
            {
                rotate(u->child[0]->child[1]);
                rotate(u->child[0]);
            }
        }
        else if (balance < -1)
        {
            if (u->child[1]->child[1]->height >= u->child[1]->child[0]->height)
                rotate(u->child[1]);
            else
            {
                rotate(u->child[1]->child[0]);
                rotate(u->child[1]);
            }
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

        if (x < u->s)
        {
            u = u->child[0];
        }
        else
        {
            u = u->child[1];
        }
    }
    u = new Node{1, 0, x, x, p, dummyptr, dummyptr};
    if (p != dummyptr)
    {
        if (x < p->s)
        {
            p->child[0] = u;
        }
        else
        {
            p->child[1] = u;
        }
    }
    else
    {
        tree.root = u;
    }
    update_and_balance(u);
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
    Node *p = u->parent;
    if (u == dummyptr)
    {
        return;
    }
    if (u->child[0] == dummyptr && u->child[1] == dummyptr)
    {
        if (p != dummyptr)
        {
            if (u == p->child[0])
            {
                p->child[0] = dummyptr;
            }
            else
            {
                p->child[1] = dummyptr;
            }
        }
        else
        {
            tree.root = dummyptr;
        }

        u->child[0] = dummyptr;
        u->child[1] = dummyptr;
        delete u;
        update_and_balance(p);
    }

    else if (u->child[0] == dummyptr)
    {
        if (p != dummyptr)
        {

            if (u == p->child[0])
            {
                p->child[0] = u->child[1];
            }
            else
            {
                p->child[1] = u->child[1];
            }

            u->child[1]->parent = p;
        }
        else
        {
            tree.root = u->child[1];
            u->child[1]->parent = dummyptr;
        }

        u->child[0] = dummyptr;
        u->child[1] = dummyptr;
        delete u;
        update_and_balance(p);
    }
    else if (u->child[1] == dummyptr)
    {
        if (p != dummyptr)
        {
            if (u == p->child[0])
            {
                p->child[0] = u->child[0];
            }
            else
            {
                p->child[1] = u->child[0];
            }
            u->child[0]->parent = p;
        }
        else
        {
            tree.root = u->child[0];
            u->child[0]->parent = dummyptr;
        }

        u->child[0] = dummyptr;
        u->child[1] = dummyptr;
        delete u;
        update_and_balance(p);
    }

    else
    {
        Node *v = u->child[1];
        while (v->child[0] != dummyptr)
        {
            v = v->child[0];
        }
        u->s = v->s;
        Node *parent = v->parent;
        if (v->child[1] != dummyptr)
        {
            if (parent != dummyptr)
            {
                parent->child[parent->child[0] == v ? 0 : 1] = v->child[1];
                v->child[1]->parent = parent;
            }
            else
            {
                tree.root = v->child[1];
                v->child[1]->parent = dummyptr;
            }
        }
        else
        {
            if (parent != dummyptr)
            {
                parent->child[parent->child[0] == v ? 0 : 1] = dummyptr;
            }
            else
            {
                tree.root = dummyptr;
            }
        }

        /* code */

        v->child[0] = dummyptr;
        v->child[1] = dummyptr;
        delete v;
        update_and_balance(parent);
    }
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
