#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
struct TreeNode
{
    int val;
    int index;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), index(-1), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), index(-1), left(nullptr), right(nullptr) {}
    TreeNode(int x, int y) : val(x), index(y), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

TreeNode *traversal(vector<int> &inorder, int inorderBegin, int inorderEnd, vector<int> &postorder, int postorderBegin, int postorderEnd)
{
    if (postorderBegin == postorderEnd)
        return NULL;

    int rootValue = postorder[postorderEnd - 1];
    TreeNode *root = new TreeNode(rootValue);

    if (postorderEnd - postorderBegin == 1)
        return root;

    int delimiterIndex;
    for (delimiterIndex = inorderBegin; delimiterIndex < inorderEnd; delimiterIndex++)
    {
        if (inorder[delimiterIndex] == rootValue)
            break;
    }
    // 切割中序数组
    // 左中序区间，左闭右开[leftInorderBegin, leftInorderEnd)
    int leftInorderBegin = inorderBegin;
    int leftInorderEnd = delimiterIndex;
    // 右中序区间，左闭右开[rightInorderBegin, rightInorderEnd)
    int rightInorderBegin = delimiterIndex + 1;
    int rightInorderEnd = inorderEnd;

    // 切割后序数组
    // 左后序区间，左闭右开[leftPostorderBegin, leftPostorderEnd)
    int leftPostorderBegin = postorderBegin;
    int leftPostorderEnd = postorderBegin + delimiterIndex - inorderBegin; // 终止位置是 需要加上 中序区间的大小size
    // 右后序区间，左闭右开[rightPostorderBegin, rightPostorderEnd)
    int rightPostorderBegin = postorderBegin + (delimiterIndex - inorderBegin);
    int rightPostorderEnd = postorderEnd - 1; // 排除最后一个元素，已经作为节点了

    root->left = traversal(inorder, leftInorderBegin, leftInorderEnd, postorder, leftPostorderBegin, leftPostorderEnd);
    root->right = traversal(inorder, rightInorderBegin, rightInorderEnd, postorder, rightPostorderBegin, rightPostorderEnd);
    cout << root->val;
    return root;
}
bool judgepostorder(vector<int> &a)
{

    // 注意边界条件

    if (a.size() == 0)
    {
        return true;
    }

    int root = a[a.size() - 1];
    a.resize(a.size() - 1);
    // 找到划分点(第一个大于root的点)
    int divide;
    for (divide = 0; divide < a.size(); divide++)
    {
        if (a[divide] > root)
        {
            break;
        }
    }

    // 如果存在后半序列，则判断是否都大于root

    for (int j = divide; j < a.size(); j++)
    {
        if (a[j] < root)
            return false; // 不满足
    }

    vector<int> left(a.begin(), a.begin() + divide);
    vector<int> right(a.begin() + divide, a.end());
    // 各自递归
    return judgepostorder(left) && judgepostorder(right);
}
int main()
{
    int n;
    cin >> n;
    vector<int> inorder;
    vector<int> postorder;
    for (int i = 0; i < n; i++)
    {
        int val;
        cin >> val;
        inorder.push_back(val);
        // inorder[i] = i + 1;
        postorder.push_back(val);
        // postorder[i] = i + 1;
    }

    if (!judgepostorder(postorder))
    {
        cout << "Not exist";
    }
    else
    {
        sort(inorder.begin(), inorder.end());
        TreeNode *root = traversal(inorder, 0, inorder.size(), postorder, 0, postorder.size());
        root->val += 1;
    };
}
