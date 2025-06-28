struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


class Solution// 给你一个链表的头节点 head 和一个整数 val ，请你删除链表中所有满足 Node.val == val 的节点，并返回 新的头节点 。
{
public:
    ListNode *removeElements(ListNode *head, int val)
    {
        ListNode *dummyHead = new ListNode(0); // 创建新链表的方式
        dummyHead->next = head;
        ListNode *cur = dummyHead;
        while (cur->next != nullptr)
        {
            if (cur->next->val == val)
            {
                ListNode *tmp = cur->next;
                cur->next = cur->next->next;
                delete tmp;
            }
            else
            {
                cur = cur->next;
            }
        }
        ListNode *head1 = dummyHead->next;
        delete dummyHead;
        return head1;
    }
};

// 设计链表
class MyLinkedList
{
public:
    MyLinkedList()
    {
        dummyHead = new ListNode(0);
        size = 0;
    }

    int get(int index)
    {
        if (index > (size - 1) || index < 0)
        {
            return -1;
        }
        ListNode *cur = dummyHead->next;
        while (index--)
        {
            cur = cur->next;
        }
        return cur->val;
    }

    void addAtHead(int val)
    {
        ListNode *newnode = new ListNode(val);
        newnode->next = dummyHead->next;
        dummyHead->next = newnode->next;
        size++;
    }

    void addAtTail(int val)
    {
        ListNode *newnode = new ListNode(val);
        ListNode *cur = dummyHead;
        while (cur->next != nullptr)
        {
            cur = cur->next;
        }
        cur->next = newnode;
        size++;
    }

    void addAtIndex(int index, int val)
    {
        if (index > (size) || index < 0)
        {
            return;
        }
        ListNode *newnode = new ListNode(val);
        ListNode *cur = dummyHead;
        while (index--) // 找到第index节点的写法
        {
            cur = cur->next; // 第零个结点cur->next指向的就是我们要的第零个，能保证cur是我们要插入的钱一个位置
        }
        newnode->next = cur->next;
        cur->next = newnode;
        size++;
    }

    void deleteAtIndex(int index)
    {
        if (index > (size) || index < 0)
        {
            return;
        }
        ListNode *cur = dummyHead; // 直到前一个节点的指针才能删掉这个节点。
        while (index--)
        {
            cur = cur->next;
        }
        ListNode *tmp = cur->next;
        cur->next = cur->next->next;
        delete tmp;
        size--;
    }

private:
    int size;
    ListNode *dummyHead;
};

// 反转链表
class Solution
{
public:
    ListNode *reverseList(ListNode *head)
    {
        ListNode *cur = head;
        ListNode *pre = nullptr;
        ListNode *temp;
        while (cur)
        { // cur是null的时候就不需要再让cur的next指向pre
            temp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = temp; // 注意顺序
        }
        return pre;
    }
}; // 递归写法
class Solution
{
public:
    ListNode *reverse(ListNode *pre, ListNode *cur)
    {
        if (cur == nullptr)
            return pre;
        ListNode *temp = cur->next;
        cur->next = pre;
        reverse(cur, temp);
    }
    ListNode *reverseList(ListNode *head)
    {

        return reverse(nullptr, head);
    }
};

// 删除倒数第n个节点
class Solution
{
public:
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        ListNode *dummyhead = new ListNode(0);
        dummyhead->next = head;
        ListNode *slow = dummyhead;
        ListNode *fast = dummyhead;
        n++; // 防止越界，让fast走n+1步
        while (n-- && fast != nullptr)
            fast = fast->next;
        while (fast != nullptr)
        {
            fast = fast->next;
            slow = slow->next;
        }
        slow->next = slow->next->next;
        return dummyhead->next;
    }
};
// 环形链表
class Solution
{
public:
    ListNode *detectCycle(ListNode *head)
    {
        ListNode *fast = head;
        ListNode *slow = head;
        while (fast != nullptr && fast->next != nullptr)
        {
            fast = fast->next->next;
            slow = slow->next;
            if (fast == slow)
            {
                ListNode *index1 = fast;
                ListNode *index2 = head;
                while (index1 != index2)
                {
                    index1 = index1->next;
                    index2 = index2->next;
                }
                return index1;
            }
        }
        return nullptr;
    }
};

// 1234

