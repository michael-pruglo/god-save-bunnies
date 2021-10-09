#include "gtest/gtest.h"
#include <src/utility/DoublyLinkedList.hpp>

TEST(DLList, Ctor)
{
    DoublyLinkedList<int> l;
    EXPECT_EQ(l.size(), 0);
}

TEST(DLList, PushBack)
{
    DoublyLinkedList<int> l;
    l.push_back(3);
    EXPECT_EQ(l.size(), 1);
    l.push_back(7);
    l.push_back(0);
    l.push_back(2);
    EXPECT_EQ(l.size(), 4);
}

TEST(DLList, ForEach)
{
    DoublyLinkedList<int> l;
    l.push_back(6);
    l.push_back(6);
    for (const auto& i: l)
        EXPECT_EQ(i, 6);
}

template<typename T>
void expect_contents(const DoublyLinkedList<T>& l, const std::vector<T>& exp_contents)
{
    ASSERT_EQ(l.size(), exp_contents.size());
    size_t i = 0;
    for (const auto& val : l)
        EXPECT_EQ(val, exp_contents[i++]);
}

TEST(DLList, Contents)
{
    DoublyLinkedList<int> l;
    std::vector<int> contents = {8,9,10,11,12,13,14};
    for (const auto& x: contents)
        l.push_back(x);
    expect_contents(l, contents);
}

TEST(DLList, IteratesBeginToEnd)
{
    DoublyLinkedList<int> l;
    std::vector<int> contents = {8,9,10,11,12,13,14};
    for (const auto& x: contents)
        l.push_back(x);

    EXPECT_EQ(*l.begin(), contents.front());

    size_t i = 0;
    for (auto it = l.begin(); it != l.end(); ++it, ++i)
        EXPECT_EQ(*it, contents[i]);
}

TEST(DLList, BeginEndIterators)
{
    DoublyLinkedList<int> l;
    EXPECT_EQ(l.begin(), l.end());
    l.push_back(1);
    EXPECT_EQ(++l.begin(), l.end());
    EXPECT_NE(l.begin(), l.end());
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.push_back(5);
    l.push_back(6);
    EXPECT_EQ(l.size(), 6);
    auto it = l.begin();
    for (int i = 0; i < 6; ++i)
    {
        EXPECT_NE(it, l.end());
        ++it;
    }
    EXPECT_EQ(it, l.end());
}

TEST(DLList, Erase)
{
    DoublyLinkedList<int> l;
    std::vector<int> contents = {1,2,3,4};
    for (const auto& x: contents)
        l.push_back(x);

    EXPECT_EQ(l.size(), contents.size());
    l.erase(l.begin());
    expect_contents(l, {2,3,4});
    l.erase(++l.begin());
    expect_contents(l, {2,4});
    l.erase(++l.begin());
    expect_contents(l, {2});
    l.erase(l.begin());
    EXPECT_EQ(l.size(), 0);
}

TEST(DLList, PushBackOnTheFly)
{
    DoublyLinkedList<int> l;
    for (const auto& x: {1,2,3,4})
        l.push_back(x);

    std::vector<int> res;
    const auto endit = l.end();
    for (auto it = l.begin(); it != endit; ++it)
    {
        if (*it%2)
            l.push_back(9 + *it);
        res.push_back(*it);
    }
    EXPECT_EQ(l.size(), 6);
    EXPECT_EQ(res.size(), 4);
    EXPECT_EQ(res[0], 1);
    EXPECT_EQ(res[1], 2);
    EXPECT_EQ(res[2], 3);
    EXPECT_EQ(res[3], 4);
}