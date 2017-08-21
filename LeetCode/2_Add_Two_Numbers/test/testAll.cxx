#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "impl.hpp"

ListNode* createList(std::initializer_list<unsigned int> numbers)
{
    ListNode *head = nullptr;
    ListNode *node = nullptr;

    for (auto n : numbers)
    {
        auto *p = new ListNode(n);
        if (node)
        {
            node->next = p;
            node = node->next;
        }
        if (!head)
        {
            head = node = p;
        }
    }

    return head;
}

bool compareList(const ListNode *l1, const ListNode *l2)
{
    do
    {
        if (!l1 && !l2)
        {
            break;
        }
        else if (l1 && l2)
        {
            if (l1->val != l2->val)
            {
                return false;
            }
            l1 = l1->next;
            l2 = l2->next; 
        }
        else
        {
            return false;
        }
    } while (true);
    return true;
}

TEST(Correctness, SimpleInput)
{
    auto *l1 = createList({2,4,4});
    auto *l2 = createList({5,6,4});

    auto *answer = createList({7,0,9});
    
    Solution_1 slu1;
    EXPECT_EQ(true, compareList(answer, slu1.addTwoNumbers(l1, l2)));

    Solution_2 slu2;
    EXPECT_EQ(true, compareList(answer, slu2.addTwoNumbers(l1, l2)));
}

