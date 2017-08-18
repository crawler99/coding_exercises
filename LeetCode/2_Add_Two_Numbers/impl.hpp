#include <cstdio>

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution_1 /* Best timing */
{
    public:
        ListNode* addTwoNumbers(ListNode *l1, ListNode *l2)
        {
            ListNode *rst = nullptr;
            ListNode *k = rst;
            ListNode *p = rst;
            unsigned int carry { 0 };

            while (l1 || l2 || carry)
            {
                k = new ListNode(carry);
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

                carry = (k->val > 9 ? 1 : 0);
                k->val -= 10 * carry;
            }

            return rst;
        }
};

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
class Solution_2
{
    public:
        ListNode* addTwoNumbers(ListNode *l1, ListNode *l2)
        {
            ListNode *rst = new ListNode(0);
            ListNode *cur = rst;
            unsigned int carry { 0 };

            while (l1 || l2 || carry)
            {
                cur->next = new ListNode(carry);
                cur = cur->next;

                if (l1) { cur->val += l1->val; l1 = l1->next; }
                if (l2) { cur->val += l2->val; l2 = l2->next; }

                carry = (cur->val > 9 ? 1 : 0);
                cur->val -= (10 * carry);
            }

            return rst->next;
        }
};

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
void dumpList(const ListNode *list)
{
    while (list)
    {
        printf("[%d]->", list->val);
        list = list->next;
    }
    printf("\n");
}

