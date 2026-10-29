#include "tstack.h"
#include <gtest/gtest.h>

TEST(TStack, can_create_stack_with_positive_size) {
    ASSERT_NO_THROW(TStack<int> s(5));
}

TEST(TStack, throws_when_create_stack_with_negative_size) {
    ASSERT_ANY_THROW(TStack<int> s((size_t)-5));
}

TEST(TStack, new_stack_is_empty) {
    TStack<int> s(5);
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(0, s.size());
}

TEST(TStack, can_push_and_top) {
    TStack<int> s(5);
    s.push(10);
    s.push(20);
    EXPECT_EQ(2, s.size());
    EXPECT_EQ(20, s.top()); // Последний пришел - первый вышел
}

TEST(TStack, can_pop) {
    TStack<int> s(5);
    s.push(10);
    s.push(20);
    s.pop();
    EXPECT_EQ(1, s.size());
    EXPECT_EQ(10, s.top());
}

TEST(TStack, throws_when_pop_empty_stack) {
    TStack<int> s(5);
    ASSERT_ANY_THROW(s.pop());
}

TEST(TStack, throws_when_top_empty_stack) {
    TStack<int> s(5);
    ASSERT_ANY_THROW(s.top());
}

TEST(TStack, can_copy_stack) {
    TStack<int> s1(5);
    s1.push(1);
    s1.push(2);
    TStack<int> s2(s1);

    EXPECT_EQ(s1.size(), s2.size());
    EXPECT_EQ(s1.top(), s2.top());
}

TEST(TStack, copied_stack_has_its_own_memory) {
    TStack<int> s1(5);
    s1.push(1);
    TStack<int> s2(s1);

    s2.push(99); // Меняем копию
    EXPECT_EQ(1, s1.size()); // Оригинал не изменился
}

TEST(TStack, can_assign_stack_to_itself) {
    TStack<int> s(5);
    s.push(10);
    ASSERT_NO_THROW(s = s);
    EXPECT_EQ(10, s.top());
}

TEST(TStack, throws_when_push_too_many_elements)
{
    TStack<int> s(2); // Вместимость 2
    s.push(1);
    s.push(2);
    s.push(3); // Должен расшириться из-за Resize

    EXPECT_EQ(3, s.size());
    EXPECT_EQ(3, s.top());
}

TEST(TStack, can_clear_stack)
{
    TStack<int> s(5);
    s.push(1);
    s.push(2);
    s.clear();

    EXPECT_TRUE(s.empty());
    EXPECT_EQ(0, s.size());
}

TEST(TStack, can_assign_stack_of_equal_size)
{
    TStack<int> s1(5), s2(5);
    s1.push(10);
    s2 = s1;

    EXPECT_EQ(1, s2.size());
    EXPECT_EQ(10, s2.top());
}

TEST(TStack, can_assign_stack_of_different_size)
{
    TStack<int> s1(2), s2(10);
    s1.push(5);
    s1.push(6);

    s2 = s1;

    EXPECT_EQ(2, s2.size());
    EXPECT_EQ(6, s2.top());
}

TEST(TStack, can_move_stack)
{
    TStack<int> s1(5);
    s1.push(1);
    s1.push(2);

    TStack<int> s2(std::move(s1)); // Перемещение

    EXPECT_EQ(2, s2.size());
    EXPECT_EQ(2, s2.top());
    EXPECT_TRUE(s1.empty()); // Старый стек должен стать пустым
}

TEST(TStack, push_and_pop_many_times)
{
    TStack<int> s(5);
    for (int i = 0; i < 100; i++) s.push(i);
    for (int i = 0; i < 100; i++) s.pop();

    EXPECT_TRUE(s.empty());
}