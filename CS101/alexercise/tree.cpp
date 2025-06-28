#include <stack>
#include <queue>
#include <string>
#include <vector>
#include <deque>
#include <unordered_map>
#include <queue>
#include <algorithm>
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
// 前序遍历
class Solution
{
public:
    void traversal(TreeNode *cur, vector<int> &vec)
    {
        if (cur == NULL)
            return;
        vec.push_back(cur->val);
        traversal(cur->left, vec);
        traversal(cur->right, vec);
    }
    vector<int> preorderTraversal(TreeNode *root)
    {
        vector<int> result;
        traversal(root, result);
        return result;
    }
};
// 中序遍历
class Solution
{
public:
    void traversal(TreeNode *cur, vector<int> &vec)
    {
        if (cur == NULL)
            return;

        traversal(cur->left, vec);
        vec.push_back(cur->val);
        traversal(cur->right, vec);
    }
    vector<int> inorderTraversal(TreeNode *root)
    {
        vector<int> result;
        traversal(root, result);
        return result;
    }
};
// 后序
class Solution
{
public:
    void traversal(TreeNode *cur, vector<int> &vec)
    {
        if (cur == NULL)
            return;

        traversal(cur->left, vec);

        traversal(cur->right, vec);
        vec.push_back(cur->val);
    }
    vector<int> postorderTraversal(TreeNode *root)
    {
        vector<int> result;
        traversal(root, result);
        return result;
    }
};
// 非递归遍历
class Solution
{
public:
    vector<int> postorderTraversal(TreeNode *root)
    {
        vector<int> result;
        stack<TreeNode *> st;
        st.push(root);
        TreeNode *node;
        while (!st.empty())
        {
            node = st.top();
            st.pop();
            if (node != nullptr)
            {
                result.push_back(node->val); // 中
            }
            else
            {
                continue;
            }
            st.push(node->right); // 右
            st.push(node->left);  // 左
        }
        return result;
    }
};
class Solution // 后续遍历
{
public:
    vector<int> postorderTraversal(TreeNode *root)
    {
        vector<int> result;
        stack<TreeNode *> st;
        st.push(root);
        TreeNode *node;
        while (!st.empty())
        {
            node = st.top();
            st.pop();
            if (node != nullptr)
            {
                result.push_back(node->val); // 中
            }
            else
            {
                continue;
            }

            st.push(node->left);  // 左
            st.push(node->right); // 右
        }
        reverse(result.begin(), result.end());
        return result;
    }
};
class Solution // 中序
{
public:
    vector<int> inorderTraversal(TreeNode *root)
    {
        vector<int> result;
        stack<TreeNode *> st;
        TreeNode *cur = root;
        while (cur != nullptr || !st.empty())
        {
            if (cur != nullptr)
            {
                st.push(cur);
                cur = cur->left;
            }
            else
            {
                cur = st.top();
                st.pop();
                result.push_back(cur->val);
                cur = cur->right;
            }
        }
        return result;
    }
};

// 层序遍历,最小深度
class Solution
{
public:
    int minDepth(TreeNode *root)
    {
        queue<TreeNode *> que;
        TreeNode *node;
        int depth = 0;
        int min_layer = INT_MAX;
        if (root != NULL)
            que.push(root);
        while (!que.empty())
        {
            int size = que.size(); // 不记录的话容易和下一层的元素一起弹出来，这是控制弹出数目
            vector<int> vec;
            depth++;
            while (size--) // 在循环里que的size是不断变化的
            {
                node = que.front();
                que.pop();
                vec.push_back(node->val);
                if (node->left)
                    que.push(node->left);
                if (node->right)
                    que.push(node->right);
                if (!node->right && !node->left)
                {
                    return depth;
                }
            }
        }
        return min_layer == INT_MAX ? 0 : min_layer;
    }
};
// 最小深度
class Solution
{
public:
    int getheight(TreeNode *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        int leftheight = getheight(node->left);

        int rightheight = getheight(node->right);
        if (node->left == nullptr && node->right != nullptr)
        {
            return 1 + rightheight;
        }
        else if (node->left != nullptr && node->right == nullptr)
        {
            return 1 + leftheight;
        }
        else
            return min(leftheight, rightheight) + 1;
    }
    int minDepth(TreeNode *root)
    {
        return getheight(root);
    }
};
// 翻转二叉树
class Solution
{
public:
    TreeNode *invertTree(TreeNode *root)
    {
        if (root == nullptr) // root是指操作的变量
            return root;
        swap(root->left, root->right); // 中
        invertTree(root->left);        // 左
        invertTree(root->right);       // 右

        return root;
    }
};

// 对称二叉树
class Solution
{
public:
    bool compare(TreeNode *left, TreeNode *right)
    {
        if (left == nullptr && right != nullptr)
            return false;
        else if (left != nullptr && right == nullptr)
            return false;
        else if (left == nullptr && right == nullptr) // 第二层就是两个都为空就可以直接返回。
            // 剩下的内部节点由bool inside = compare(left->right, right->left)检查
            // 到最终两个节点都是空就直接返回true。
            return true;
        else if (left->val != right->val)
            return false;
        bool outside = compare(left->left, right->right);
        bool inside = compare(left->right, right->left);
        bool result = outside & inside;
        return result;
    };

    bool isSymmetric(TreeNode *root)
    {
        if (root == nullptr)
            return true;
        return compare(root->left, root->right);
    }
};

// 二叉树的最大深度
class Solution
{
public:
    int getheight(TreeNode *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        int leftheight = getheight(node->left);

        int rightheight = getheight(node->right);
        int height = max(leftheight, rightheight) + 1;
        return height;
    }
    int maxDepth(TreeNode *root)
    {
        return getheight(root);
    }
};

// 平衡二叉树
class Solution
{
public:
    int getHeight(TreeNode *node)
    {
        if (node == nullptr)
        {
            return 0;
        }
        int leftHeight = getHeight(node->left);
        if (leftHeight == -1)
            return -1;
        int rightHeight = getHeight(node->right);
        if (rightHeight == -1)
            return -1;

        return abs(leftHeight - rightHeight) > 1 ? -1 : 1 + max(leftHeight, rightHeight);
    }
    bool isBalanced(TreeNode *root)
    {
        return getHeight(root) == -1 ? false : true;
    }
};
// 二叉树的所有路劲
class Solution
{
public:
    void traversal(TreeNode *node, vector<int> &path, vector<string> &result)
    {
        path.push_back(node->val); // middle

        if (node->left == nullptr && node->right == nullptr)
        {
            string sPath;
            for (int i = 0; i < path.size() - 1; i++)
            {
                sPath += to_string(path[i]);
                sPath += "->";
            }
            sPath += to_string(path[path.size() - 1]);

            result.push_back(sPath);
        }
        if (node->left)
        {
            traversal(node->left, path, result);
            path.pop_back(); // 回溯
        }
        if (node->right)
        {
            traversal(node->right, path, result);
            path.pop_back(); // 回溯
        }
    };
    vector<string> binaryTreePaths(TreeNode *root)
    {
        vector<string> result;
        vector<int> path;
        if (root == nullptr)
            return result;
        traversal(root, path, result);
        return result;
    }
};

// 路径总和
class Solution
{
public:
    bool traversal(TreeNode *node, int count)
    {
        if (node->left == nullptr && node->right == nullptr && count == 0)
            return true;
        if (node->left == nullptr && node->right == nullptr && count != 0)
            return false;
        if (node->left)
        {
            count -= node->left->val;
            if (traversal(node->left, count))
                return true;
            count += node->left->val; // 回溯
        }
        if (node->right)
        {
            count -= node->right->val;
            if (traversal(node->right, count))
                return true;
            count += node->right->val;
        }
        return false;
    }
    bool hasPathSum(TreeNode *root, int targetSum)
    {
        if (root == nullptr)
            return false;
        return traversal(root, targetSum - root->val);
    }
};
// 使用中序与后序序列构造二叉树
class Solution
{
public:
    TreeNode *traversal(vector<int> &inorder, vector<int> &postorder)
    {
        if (postorder.size() == 0)
            return NULL;
        int rootvalue = postorder[postorder.size() - 1]; // 先找到根节点
        TreeNode *root = new TreeNode(rootvalue);
        if (postorder.size() == 1)
            return root;
        int index = 0;
        for (index = 0; index < inorder.size(); index++)
        {
            if (inorder[index] == rootvalue)
                break;
        } // index定义在for循环外面来保存在中序数组中找到的中节点的位置
        // 用index切中序数组 得左中序和右中序
        vector<int> leftInorder(inorder.begin(), inorder.begin() + index);
        vector<int> rightInorder(inorder.begin() + index + 1, inorder.end());
        // 用中序数组里左中序数组大小切后序数组
        postorder.resize(postorder.size() - 1);
        vector<int> leftPostorder(postorder.begin(), postorder.begin() + leftInorder.size());
        vector<int> rightPostorder(postorder.begin() + leftInorder.size(), postorder.end());

        root->left = traversal(leftInorder, leftPostorder);
        root->right = traversal(rightInorder, rightPostorder);
        return root;
    }
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
    {
        return traversal(inorder, postorder);
    }
};

// 二叉搜索树中的搜索
class Solution
{
public:
    TreeNode *searchBST(TreeNode *root, int val)
    {
        if (root == NULL || root->val == val)
            return root;
        TreeNode *result = nullptr;
        if (val < root->val)
        {
            result = searchBST(root->left, val);
        }
        if (val > root->val)
        {
            result = searchBST(root->right, val);
        }
        return result;
    }
};
class Solution // 迭代法
{
public:
    TreeNode *searchBST(TreeNode *root, int val)
    {
        while (root != nullptr)
        {
            if (val < root->val)
            {
                root = root->left;
            }
            else if (val > root->val)
                root = root->right;
            else
                return root;
        }
        return nullptr;
    }
};
// 验证二叉搜索树
// 使用数组法

class Solution
{
public:
    vector<int> result;
    bool isValidBST(TreeNode *root)
    {

        if (root == nullptr)
        {
            return true;
        }
        if (!isValidBST(root->left))
            return false;
        result.push_back(root->val);
        if (!isValidBST(root->right))
            return false;
        for (int i = 1; i < result.size(); i++)
        {
            if (result[i] <= result[i - 1])
            {
                return false;
            }
        }
        return true;
    }
};
// 不使用数组
class Solution
{
public:
    long long maxVal = LONG_MIN;
    bool isValidBST(TreeNode *root)
    {
        if (root == nullptr)
        {
            return true;
        }
        bool left = isValidBST(root->left);
        if (root->val > maxVal)
        {
            maxVal = root->val; // maxVal record the previous node's val,since the inorder ascendingue
        }
        else
            return false;
        bool right = isValidBST(root->right);
        return left && right;
    }
};
// 不使用额外变量的双指针法

class Solution
{
public:
    TreeNode *pre = nullptr;
    bool isValidBST(TreeNode *root)
    {
        if (root == nullptr)
        {
            return true;
        }
        bool left = isValidBST(root->left);
        if (pre != nullptr && root->val <= pre->val)

            return false;
        pre = root; // use pointer pre to record the previous node
        bool right = isValidBST(root->right);
        return left && right;
    }
};

// 二叉搜索树最小绝对值
class Solution
{
public:
    int result = INT_MAX;
    TreeNode *pre = nullptr;
    void traversal(TreeNode *cur)
    {
        if (cur == nullptr)
            return;
        traversal(cur->left);
        if (pre != nullptr)
        {
            result = min(result, cur->val - pre->val);
        }
        pre = cur;
        traversal(cur->right);
    };
    int getMinimumDifference(TreeNode *root)
    {
        traversal(root);
        return result;
    }
};

// 求二叉搜索树中的众数
class Solution
{
public:
    int count = 1;
    int maxCount = 0;
    vector<int> result;
    TreeNode *pre;
    void traversal(TreeNode *cur)
    {
        if (cur == nullptr)
            return;
        traversal(cur->left);
        if (pre != nullptr)
        {
            if (pre->val == cur->val)
            {
                count++;
            }
            else
                count = 1;
        }
        pre = cur;

        if (count == maxCount)
            result.push_back(cur->val); // 必须放在下一个判断条件的上面
        if (count > maxCount)
        {
            maxCount = count;
            result.clear();
            result.push_back(cur->val);
        } // 一旦更新了maxcount说明前面记录的值都不是最大的
        traversal(cur->right);
    };
    vector<int> findMode(TreeNode *root)
    {
        traversal(root);
        return result;
    }
};

// 求二叉树最近的公共祖先
// 普通二叉树
class Solution
{
public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        if (root == nullptr)
        {
            return root;
        }
        if (root == p || root == q)
        {
            return root;
        }
        TreeNode *left = lowestCommonAncestor(root->left, p, q);
        TreeNode *right = lowestCommonAncestor(root->right, p, q);
        if (left != nullptr && right != nullptr)
        {
            return root;
        }
        else if (left == nullptr && right != nullptr)
        {
            return right;
        }
        else if (left != nullptr && right == nullptr)
        {
            return left;
        }
        else
            return nullptr;
    }
};
// 二叉搜索树
class Solution
{
public:
    TreeNode *traversal(TreeNode *cur, TreeNode *p, TreeNode *q)
    {
        if (cur == nullptr)
        {
            return cur;
        }
        if (cur->val > p->val && cur->val > q->val)
        {
            TreeNode *left = traversal(cur->left, p, q);
            if (left != nullptr)
                return left;
        }
        if (cur->val < p->val && cur->val < q->val)
        {
            TreeNode *right = traversal(cur->right, p, q);
            if (right != nullptr)
            {
                return right;
            }
        }
        return cur; // 包含了节点本身是公共祖先的情况。
    }
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        return traversal(root, p, q);
    }
};
// 二叉搜索树的插入操作
class Solution
{
public:
    TreeNode *insertIntoBST(TreeNode *root, int val)
    {
        if (root == nullptr)
        {
            TreeNode *node = new TreeNode(val);
            return node;
        }
        if (val < root->val)
        {
            root->left = insertIntoBST(root->left, val);
        }
        if (val > root->val)
        {
            root->right = insertIntoBST(root->right, val);
        }
        return root;
    }
};

// 二叉树中删除节点
class Solution
{
public:
    TreeNode *deleteNode(TreeNode *root, int key)
    {
        if (root == nullptr)
        {
            return nullptr;
        }
        if (root->val == key)
        {
            if (root->left == nullptr && root->right == nullptr)
            {
                delete root;
                return nullptr;
            }
            else if (root->left != NULL && root->right == nullptr)
            {
                TreeNode *tmp = root;
                root = root->left;
                delete tmp;
                return root;
            }
            else if (root->right != NULL && root->left == nullptr)
            {
                TreeNode *tmp = root;
                root = root->right;
                delete tmp;
                return root;
            }
            else
            {
                TreeNode *cur = root->right;
                while (cur->left != nullptr)
                {
                    cur = cur->left;
                }
                cur->left = root->left;
                TreeNode *tmp = root;
                root = root->right;
                delete tmp;
                return root; // 变成左为空右不为空的情况。
            }
        }
        if (key < root->val)
        {
            root->left = deleteNode(root->left, key);
        }
        if (key > root->val)
        {
            root->right = deleteNode(root->right, key);
        }
        return root;
    }
};
// 修建二叉树
class Solution
{
public:
    TreeNode *trimBST(TreeNode *root, int low, int high)
    {
        if (root == nullptr)
        {
            return nullptr;
        }
        if (root->val < low)
        {
            TreeNode *right = trimBST(root->right, low, high);
            return right; // 修右子树
        }
        if (root->val > high)
        {
            TreeNode *left = trimBST(root->left, low, high);
            return left; // 修左子树
        }
        root->left = trimBST(root->left, low, high);
        root->right = trimBST(root->right, low, high);
        return root;
    }
};

// 构造一棵平衡二叉搜索树
class Solution
{
public:
    TreeNode *traversal(vector<int> &nums, int left, int right) // 左闭右闭
    {
        if (left > right)
        {
            return nullptr;
        }
        int mid = (left + right) / 2;
        TreeNode *root = new TreeNode(nums[mid]);
        root->left = traversal(nums, left, mid - 1);
        root->right = traversal(nums, mid + 1, right);
        return root;
    }
    TreeNode *sortedArrayToBST(vector<int> &nums)
    {
        TreeNode *root = traversal(nums, 0, nums.size() - 1);
        return root;
    }
};