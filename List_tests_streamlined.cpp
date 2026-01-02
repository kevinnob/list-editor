#include "List.hpp"
#include "unit_test_framework.hpp"
#include <vector>

using namespace std;

// Streamlined comprehensive List tests

TEST(test_empty_and_size) {
    List<int> lst;
    ASSERT_TRUE(lst.empty());
    ASSERT_EQUAL(lst.size(), 0);
    lst.push_back(1);
    ASSERT_FALSE(lst.empty());
    ASSERT_EQUAL(lst.size(), 1);
}

TEST(test_push_and_pop_front_back) {
    List<int> lst;
    lst.push_front(2);
    lst.push_front(1);
    lst.push_back(3);
    lst.push_back(4);
    ASSERT_EQUAL(lst.front(), 1);
    ASSERT_EQUAL(lst.back(), 4);
    ASSERT_EQUAL(lst.size(), 4);
    
    lst.pop_front();
    ASSERT_EQUAL(lst.front(), 2);
    lst.pop_back();
    ASSERT_EQUAL(lst.back(), 3);
    ASSERT_EQUAL(lst.size(), 2);
}

TEST(test_begin_and_end) {
    List<int> lst;
    ASSERT_TRUE(lst.begin() == lst.end());
    lst.push_back(42);
    ASSERT_FALSE(lst.begin() == lst.end());
    ASSERT_EQUAL(*lst.begin(), 42);
}

TEST(test_insert_variants) {
    List<int> lst;
    // Insert at begin (empty)
    auto it = lst.insert(lst.begin(), 2);
    ASSERT_EQUAL(*it, 2);
    
    // Insert at begin (non-empty)
    it = lst.insert(lst.begin(), 1);
    ASSERT_EQUAL(*it, 1);
    
    // Insert at end
    it = lst.insert(lst.end(), 4);
    ASSERT_EQUAL(*it, 4);
    
    // Insert in middle
    it = lst.begin();
    ++it; ++it;
    it = lst.insert(it, 3);
    ASSERT_EQUAL(*it, 3);
    
    vector<int> expected{1, 2, 3, 4};
    ASSERT_SEQUENCE_EQUAL(lst, expected);
}

TEST(test_erase_variants) {
    List<int> lst;
    for (int i = 1; i <= 4; ++i) lst.push_back(i);
    
    // Erase from middle
    auto it = lst.begin();
    ++it; ++it;
    it = lst.erase(it);
    ASSERT_EQUAL(*it, 4);
    
    // Erase from beginning
    it = lst.erase(lst.begin());
    ASSERT_EQUAL(*it, 2);
    
    // Erase last element returns end
    it = lst.end();
    --it;
    it = lst.erase(it);
    ASSERT_TRUE(it == lst.end());
    ASSERT_EQUAL(lst.size(), 1);
}

TEST(test_clear) {
    List<int> lst;
    for (int i = 0; i < 10; ++i) lst.push_back(i);
    lst.clear();
    ASSERT_TRUE(lst.empty());
    ASSERT_TRUE(lst.begin() == lst.end());
}

TEST(test_copy_constructor) {
    List<int> a;
    for (int i = 1; i <= 3; ++i) a.push_back(i);
    
    List<int> b = a;
    ASSERT_EQUAL(b.size(), 3);
    ASSERT_SEQUENCE_EQUAL(a, b);
    
    // Verify deep copy
    a.pop_back();
    ASSERT_EQUAL(a.size(), 2);
    ASSERT_EQUAL(b.size(), 3);
}

TEST(test_assignment_operator) {
    List<int> a, b;
    for (int i = 1; i <= 3; ++i) a.push_back(i);
    for (int i = 10; i <= 12; ++i) b.push_back(i);
    
    // Regular assignment
    b = a;
    ASSERT_SEQUENCE_EQUAL(a, b);
    
    // Self-assignment via reference
    List<int>& ref = b;
    b = ref;
    ASSERT_EQUAL(b.size(), 3);
    
    // Assignment from empty
    List<int> empty;
    b = empty;
    ASSERT_TRUE(b.empty());
}

TEST(test_iterator_equality) {
    List<int>::Iterator default1, default2;
    ASSERT_TRUE(default1 == default2);
    
    List<int> lst;
    lst.push_back(1);
    auto it = lst.begin();
    ASSERT_FALSE(default1 == it);
    
    auto it2 = lst.begin();
    ASSERT_TRUE(it == it2);
}

TEST(test_iterator_increment_decrement) {
    List<int> lst;
    for (int i = 1; i <= 3; ++i) lst.push_back(i);
    
    // Prefix increment
    auto it = lst.begin();
    ASSERT_EQUAL(*it, 1);
    ++it;
    ASSERT_EQUAL(*it, 2);
    
    // Postfix increment
    auto old = it++;
    ASSERT_EQUAL(*old, 2);
    ASSERT_EQUAL(*it, 3);
    
    // Prefix decrement
    --it;
    ASSERT_EQUAL(*it, 2);
    
    // Postfix decrement  
    old = it--;
    ASSERT_EQUAL(*old, 2);
    ASSERT_EQUAL(*it, 1);
}

TEST(test_iterate_backwards_from_end) {
    List<int> lst;
    for (int i = 1; i <= 4; ++i) lst.push_back(i);
    
    auto it = lst.end();
    --it;
    ASSERT_EQUAL(*it, 4);
    --it;
    ASSERT_EQUAL(*it, 3);
    --it;
    ASSERT_EQUAL(*it, 2);
    --it;
    ASSERT_EQUAL(*it, 1);
    ASSERT_TRUE(it == lst.begin());
}

TEST(test_iterator_dereference_and_arrow) {
    struct Point { int x, y; };
    List<Point> lst;
    lst.push_back(Point{3, 4});
    
    auto it = lst.begin();
    ASSERT_EQUAL((*it).x, 3);
    ASSERT_EQUAL(it->y, 4);
}

TEST(test_iterator_big_three) {
    List<int> lst;
    lst.push_back(10);
    lst.push_back(20);
    
    // Copy constructor
    auto it1 = lst.begin();
    auto it2 = it1;
    ASSERT_TRUE(it1 == it2);
    
    // Assignment
    List<int>::Iterator it3;
    it3 = it1;
    ASSERT_TRUE(it3 == it1);
    ASSERT_EQUAL(*it3, 10);
}

TEST_MAIN()
