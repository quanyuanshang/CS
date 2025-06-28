#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
int count(TreeNode *root)
{

    if (root == nullptr)
    {
        return 0;
    }
    int rightsum = count(root->right);
    int leftsum = count(root->left);
    return 1 + rightsum + leftsum;
}
bool isSymmetric(TreeNode *left, TreeNode *right)
{
    if (left == nullptr && right != nullptr)
    {
        return false;
    }
    else if (right == nullptr && left != nullptr)
    {
        return false;
    }
    else if (right == nullptr && left == nullptr)
    {
        return true;
    }
    else if (left->val != right->val)
    {
        return false;
    }
    bool outside = isSymmetric(left->left, right->right);
    bool inside = isSymmetric(left->right, right->left);
    return outside & inside;
}
int findmax(TreeNode *root)
{
    if (root == nullptr)
    {
        return 0;
    }

    if (isSymmetric(root->left, root->right))
    {
        return count(root);
    }

    int rightcount = findmax(root->right);
    int leftcount = findmax(root->left);
    return max(rightcount, leftcount);
}
int main()
{
    int n;
    cin >> n;
    vector<int> nodesVal(n);
    for (int i = 0; i < n; i++)
    {
        cin >> nodesVal[i];
    }
    vector<pair<int, int>> children(n);
    for (int i = 0; i < n; i++)
    {
        cin >> children[i].first >> children[i].second; // 读取每个节点的左右子节点
    }
    vector<TreeNode *> nodes(n + 1, nullptr); // 创建树。
    for (int i = 1; i <= n; i++)
    {
        nodes[i] = new TreeNode(nodesVal[i - 1]);
    }
    for (int i = 1; i <= n; i++)
    {
        int left = children[i - 1].first;
        int right = children[i - 1].second;

        if (left != -1)
        {
            nodes[i]->left = nodes[left];
        }

        if (right != -1)
        {
            nodes[i]->right = nodes[right];
        }
    }
    cout << findmax(nodes[1]);
}