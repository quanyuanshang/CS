#include <algorithm>
#include <iostream>
#include <vector>
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class MyLinkedList
{
public:
    MyLinkedList() : head(nullptr), tail(nullptr), size(0)
    {
    }
    void add(int pos)
    {
        ListNode *newnode = new ListNode(pos);
        if (!head)
        {
            head = newnode;
            tail = newnode;
            tail->next = head;
        }
        else
        {
            tail->next = newnode;
            tail = newnode;
            tail->next = head;
        }
        size++;
    }

    void removeFront()
    {
        if (!head)
            return; // Empty list
        if (head == tail)
        { // Only one node
            delete head;
            head = tail = nullptr;
        }
        else
        {
            ListNode *temp = head;
            head = head->next;
            tail->next = head;
            delete temp;
        }
        size--;
    }

    void moveToBack(int count)
    {
        if (!head || size <= 1 || count <= 0)
        {
            return; // 为空或只有一个节点，或无效移动次数
        }

        count %= size; // 计算有效的移动次数
        for (int i = 0; i < count; ++i)
        {
            ListNode *tmp = head; // 记录当前的头节点
            head = head->next;    // 更新头节点
            tail->next = tmp;     // 将原头节点链接到尾部
            tail = tmp;           // 更新尾节点
            tail->next = head;    // 确保尾节点的下一个指向新的头节点
        }
    }

    ListNode *getHead()
    {
        return head;
    }
    int getsize()
    {
        return size;
    }

private:
    ListNode *head;
    ListNode *tail;
    int size;
};

int main()
{
    int n, m, p;
    std::cin >> n >> m >> p;
    int count = 0;
    MyLinkedList children;
    std::vector<int> result;
    for (int i = 1; i <= n * m; ++i)
    {
        children.add(i);
    }

    while (children.getsize() != 0)
    {
        count++;

        if ((count) % n == 0)
        {

            result.push_back(children.getHead()->val);
        }
        children.removeFront();
        children.moveToBack(p);
    }
    std::sort(result.begin(), result.end());
    for (int pos : result)
    {
        std::cout << pos << " ";
    }
    std::cout << std::endl;
}