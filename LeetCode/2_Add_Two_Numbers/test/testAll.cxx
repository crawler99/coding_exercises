#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "impl.hpp"

TEST(Correctness, SimpleInput)
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

    Solution_2 slu2;
    dumpList(slu2.addTwoNumbers(l1, l2));
}

