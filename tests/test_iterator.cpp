#include "doctest/doctest.h"
#include "src/DoublyLinkedList.h"

TEST_SUITE("DoublyLinkedList Iterator")
{
    TEST_CASE("Iteration over DoublyLinkedList")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(10);
        list.insertAtTail(20);
        list.insertAtTail(30);

        int expected[] = {10, 20, 30};

        SUBCASE("Forward iteration using Iterator")
        {
            int idx = 0;
            for (auto it = list.begin(); it != list.end(); ++it)
            {
                CHECK(*it == expected[idx++]);
            }
            CHECK(idx == 3);
        }

        SUBCASE("Range-based for iteration")
        {
            int idx = 0;
            for (int x : list)
            {
                CHECK(x == expected[idx++]);
            }
            CHECK(idx == 3);
        }
    }

    TEST_CASE("Iterator traversal forward") {
        DoublyLinkedList<int> list;
        for(int i=1;i<=3;++i) list.insertAtTail(i);
        int expected = 1;
        for(auto it = list.begin(); it != list.end(); ++it) {
            CHECK(*it == expected);
            ++expected;
        }
    }

    TEST_CASE("Iterator traversal backward") {
        DoublyLinkedList<int> list;
        for(int i=1;i<=3;++i) list.insertAtTail(i);
        int expected = 3;
        for(auto it = --list.end(); it != list.begin(); --it) {
            CHECK(*it == expected);
            --expected;
        }
    }

    TEST_CASE("Empty list iteration does nothing")
    {
        DoublyLinkedList<int> list;
        // begin and end should be equal
        auto it = list.begin();
        CHECK(it == list.end());
        int count = 0;
        for (auto x : list)
            ++count;
        CHECK(count == 0);
    }

    TEST_CASE("Iterator remains valid after reverse")
    {
        DoublyLinkedList<int> list;
        for (int i = 0; i < 5; ++i)
            list.insertAtTail(i);
        list.reverse(); // now [4,3,2,1,0]

        int expected[] = {4, 3, 2, 1, 0};
        int idx = 0;
        for (auto it = list.begin(); it != list.end(); ++it)
        {
            CHECK(*it == expected[idx++]);
        }
        CHECK(idx == 5);
    }

    TEST_CASE("Iterator equality and inequality operators")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(100);
        auto it1 = list.begin();
        auto it2 = list.begin();
        auto itEnd = list.end();
        CHECK(it1 == it2);
        CHECK(!(it1 != it2));
        ++it2;
        CHECK(it1 != it2);
        CHECK(it2 == itEnd);
    }
}