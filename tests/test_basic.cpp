#include "doctest/doctest.h"
#include "src/DoublyLinkedList.h"

TEST_SUITE("DoublyLinkedList Basic Operations")
{

    TEST_CASE("Insert at head and tail")
    {
        DoublyLinkedList<int> list;

        SUBCASE("Insert at head")
        {
            list.insertAtHead(2);
            list.insertAtHead(1);
            CHECK(list.size() == 2);
            CHECK(list.get(0) == 1);
            CHECK(list.get(1) == 2);
        }

        SUBCASE("Insert at tail")
        {
            list.insertAtTail(1);
            list.insertAtTail(2);
            CHECK(list.size() == 2);
            CHECK(list.get(0) == 1);
            CHECK(list.get(1) == 2);
        }
    }

    TEST_CASE("Delete and reverse")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3); // [1, 2, 3]

        SUBCASE("Delete middle element")
        {
            list.deleteAt(1); // remove 2
            CHECK(list.size() == 2);
            CHECK(list.get(0) == 1);
            CHECK(list.get(1) == 3);
        }

        SUBCASE("Reverse list")
        {
            list.reverse(); // should become [3, 2, 1]
            CHECK(list.get(0) == 3);
            CHECK(list.get(2) == 1);
        }
    }
}

TEST_SUITE("DoublyLinkedList<Point> Operations")
{
    std::string pointToString(Point & p)
    {
        return "(" + std::to_string(int(p.getX())) + "," + std::to_string(int(p.getY())) + ")";
    }

    TEST_CASE("Insert and get Point")
    {
        DoublyLinkedList<Point> list;

        SUBCASE("Insert at head")
        {
            list.insertAtHead(Point(1, 2));
            list.insertAtHead(Point(3, 4));
            CHECK(list.size() == 2);
            CHECK(list.get(0) == Point(3, 4));
            CHECK(list.get(1) == Point(1, 2));
        }
    }

    TEST_CASE("To string of list<Point>")
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(9, 0));
        list.insertAtTail(Point(8, 1));
        std::string str = list.toString(pointToString);
        CHECK(str == "[(9,0), (8,1)]");
    }

    TEST_CASE("Size on empty list") {
        DoublyLinkedList<int> list;
        CHECK(list.size() == 0);
    }

    TEST_CASE("Insert at index 0 on empty list") {
        DoublyLinkedList<int> list;
        list.insertAt(0, 42);
        CHECK(list.size() == 1);
        CHECK(list.get(0) == 42);
    }

    TEST_CASE("Insert at middle index") {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(3);
        list.insertAt(1, 2); // [1,2,3]
        CHECK(list.size() == 3);
        CHECK(list.get(1) == 2);
    }

    TEST_CASE("Insert at negative index does nothing") {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAt(-1, 99);
        CHECK(list.size() == 1);
        CHECK(list.get(0) == 1);
    }

    TEST_CASE("Insert at too large index does nothing") {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAt(5, 99);
        CHECK(list.size() == 1);
        CHECK(list.get(0) == 1);
    }

    TEST_CASE("Delete at head index 0") {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.deleteAt(0); // remove 1
        CHECK(list.size() == 1);
        CHECK(list.get(0) == 2);
    }

    TEST_CASE("Delete at last index") {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.deleteAt(1); // remove 2
        CHECK(list.size() == 1);
        CHECK(list.get(0) == 1);
    }

    TEST_CASE("Delete at invalid index does nothing") {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.deleteAt(2);
        CHECK(list.size() == 1);
        CHECK(list.get(0) == 1);
    }

    TEST_CASE("Get at invalid index throws exception") {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        CHECK_THROWS_AS(list.get(1), std::out_of_range);
    }

    TEST_CASE("IndexOf existing and non-existing") {
        DoublyLinkedList<int> list;
        list.insertAtTail(5);
        list.insertAtTail(6);
        CHECK(list.indexOf(5) == 0);
        CHECK(list.indexOf(6) == 1);
        CHECK(list.indexOf(7) == -1);
    }

    TEST_CASE("Contains existing and non-existing") {
        DoublyLinkedList<int> list;
        list.insertAtTail(10);
        list.insertAtTail(20);
        CHECK(list.contains(10) == true);
        CHECK(list.contains(30) == false);
    }

    TEST_CASE("Reverse empty list") {
        DoublyLinkedList<int> list;
        list.reverse();
        CHECK(list.size() == 0);
    }

    TEST_CASE("Reverse single-element list") {
        DoublyLinkedList<int> list;
        list.insertAtTail(7);
        list.reverse();
        CHECK(list.size() == 1);
        CHECK(list.get(0) == 7);
    }

    TEST_CASE("toString default conversion") {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        std::string s = list.toString();
        CHECK(s == "[1, 2]");
    }

    TEST_CASE("toString with custom convert2str") {
        DoublyLinkedList<int> list;
        list.insertAtTail(3);
        list.insertAtTail(4);
        auto conv = [](int &x){ return std::string("#") + std::to_string(x); };
        std::string s = list.toString(conv);
        CHECK(s == "[#3, #4]");
    }

}

