#include <cstdio>

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution_1
{
    public:
        ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
        {
            ListNode *rst = nullptr;
            ListNode *k = rst;
            ListNode *p = rst;
            unsigned int carry {0};

            while (l1 || l2 || carry)
            {
                k = new ListNode(0);
                if (!rst)
                {
                    rst = p = k;
                }
                else
                {
                    p->next = k;
                    p = k;
                }

                if (l1) { k->val += l1->val; l1 = l1->next; }
                if (l2) { k->val += l2->val; l2 = l2->next; }
                k->val += carry;

                carry = (k->val > 9 ? 1 : 0);
                k->val -= 10 * carry;
            }

            return rst;
        }
};

void dumpList(const ListNode *list)
{
    while (list)
    {
        printf("[%d]->", list->val);
        list = list->next;
    }
    printf("\n");
}

int main()
{
    ListNode *node = new ListNode(2);
    ListNode *l1 = node;
    node->next = new ListNode(4);
    node = node->next;
    node->next = new ListNode(3);

    node = new ListNode(5);
    ListNode *l2 = node;
    node->next = new ListNode(6);
    node = node->next;
    node->next = new ListNode(4);

    Solution_1 slu1;
    dumpList(slu1.addTwoNumbers(l1, l2));

    return 0;
}

