#include <algorithm>
#include <iostream>
#include <vector>
#include <climits>
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

/*void traversal(vector<int> &a, int left, int right, int index)
{
    // 递归终止条件：如果数组只有 0 或 1 个元素，肯定是有效的
    if (left == right)
    {
        result.push_back(index);
        //cout << "root1:" << a[left] << endl;
        return;
    }
    if (left > right)
    {

        return;
    }

    // 当前根节点是后序遍历的最后一个元素
    int root = a[right];
    int rootindex = right + 1;
   // cout << "root2:" << root << endl;
    // 找到左子树的分界点，分界点为第一个大于根节点的位置
    int i = left;
    while (i < right && a[i] < root)
    {

        //cout << a[i] << endl;
        i++;
    }
    traversal(a, left, i - 1, rootindex);
    traversal(a, i, right - 1, rootindex);
    result.push_back(index);
    //cout << "root3:" << root << endl;
}*/
TreeNode *buildTree(vector<int> const &postorder, int &pIndex,
                    int min, int max, int index)
{
    // 基本情况
    if (pIndex < 0)
    {
        return nullptr;
    }

    // 如果后序遍历的下一个元素从末尾返回
    // 不在有效范围内
    int curr = postorder[pIndex];
    int rootindex = pIndex + 1;
    // cout << "index1:" << rootindex << endl;
    if (curr < min || curr > max)
    {
        return nullptr;
    }

    // 构造根节点并递减`pIndex`
    TreeNode *root = new TreeNode(curr);
    pIndex--;

    /* 构造根节点的左右子树。
       在左子树之前构建右子树，因为值
       正在从后序序列的末尾读取。 */

    // 因为 BST 右子树中的所有元素都必须更大
    // 比根节点的值，设置范围为 `[curr+1…max]` 并递归
    root->right = buildTree(postorder, pIndex, curr + 1, max, rootindex);

    // 因为 BST 的左子树中的所有元素都必须小于
    // 比根节点的值，设置范围为 `[min, curr-1]` 并 recur
    root->left = buildTree(postorder, pIndex, min, curr - 1, rootindex);
    root->index = index;
    // cout << "index2:" << root->index << endl;
    return root;
}
bool judgeTree(vector<int> const &postorder, int &pIndex,
               int min, int max)
{
    // 基本情况
    if (pIndex < 0)
    {
        return true;
    }

    // 如果后序遍历的下一个元素从末尾返回
    // 不在有效范围内
    int curr = postorder[pIndex];
    cout << "min:" << min << endl;
    cout << "max:" << max << endl;
    if (curr < min || curr > max)
    {
        judgeTree(postorder, pIndex, min, curr - 1);
    }
    pIndex--;
    bool right = judgeTree(postorder, pIndex, curr + 1, max);
    bool left = judgeTree(postorder, pIndex, min, curr - 1);
    return right && left;
}
/*bool judgepostorder(vector<int> &a, int left, int right)
{
    if (left >= right)
    {
        return true;
    }

    int root = a[right];

    int i = left;
    while (i < right && a[i] < root)
    {
        i++;
    }

    for (int j = i; j < right; j++)
    {
        if (a[j] < root)
        {
            return false; // 不满足后序遍历的条件
        }
    }
    return judgepostorder(a, left, i - 1) && judgepostorder(a, i, right - 1);
}*/
void intraversal(TreeNode *cur, vector<int> &vec)
{
    if (cur == NULL)
        return;

    intraversal(cur->left, vec);  // 左
    vec.push_back(cur->val);      // 中
    intraversal(cur->right, vec); // 右
}
void posttraversal(TreeNode *cur)
{
    if (cur == NULL)
        return;

    posttraversal(cur->left);

    posttraversal(cur->right);
    // vec.push_back(cur->index);
    if (cur->index != -1)
    {
        cout << cur->index << " ";
    }
}
bool Isascending(vector<int> &inorder)
{
    for (int i = 0; i < inorder.size(); i++)
    {
        if (i > 0 && inorder[i - 1] > inorder[i])
        {
            return false;
        }
    }
    return true;
}
int main()
{
    vector<int> inorder;
    int n;
    cin >> n;
    vector<int> postorder;
    for (int i = 0; i < n; i++)
    {
        int val;
        cin >> val;

        postorder.push_back(val);
        // postorder[i] = i + 1;
    }
    int pIndex = postorder.size() - 1;
    TreeNode *root = buildTree(postorder, pIndex, INT_MIN, INT_MAX, -1);
    intraversal(root, inorder);
    for (int val : inorder)
    {
        cout << val;
    }

    if (inorder.size() < postorder.size())
    {
        cout << "Not exist";
    }
    else if (inorder.size() == postorder.size())
    {

        posttraversal(root);
    };
}