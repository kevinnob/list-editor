#include "List.hpp"
#include "unit_test_framework.hpp"
#include <vector>

using namespace std;

// Unit tests for List<T>

TEST(test_empty_on_construct) {
    List<int> lst;
    ASSERT_TRUE(lst.empty());
    ASSERT_EQUAL(lst.size(), 0);
    ASSERT_TRUE(lst.begin() == lst.end());
}

TEST(test_push_front_and_push_back) {
    List<int> lst;
    lst.push_front(2);
    lst.push_front(1);
    lst.push_back(3);
    ASSERT_FALSE(lst.empty());
    ASSERT_EQUAL(lst.size(), 3);
    ASSERT_EQUAL(lst.front(), 1);
    ASSERT_EQUAL(lst.back(), 3);
}

TEST(test_pop_front_and_pop_back) {
    List<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);
    ASSERT_EQUAL(lst.size(), 3);
    lst.pop_front();
    ASSERT_EQUAL(lst.size(), 2);
    ASSERT_EQUAL(lst.front(), 2);
    lst.pop_back();
    ASSERT_EQUAL(lst.size(), 1);
    ASSERT_EQUAL(lst.back(), 2);
}

TEST(test_clear) {
    List<int> lst;
    for (int i = 0; i < 5; ++i) lst.push_back(i);
    ASSERT_EQUAL(lst.size(), 5);
    lst.clear();
    ASSERT_TRUE(lst.empty());
    ASSERT_EQUAL(lst.size(), 0);
    ASSERT_TRUE(lst.begin() == lst.end());
}

TEST(test_copy_constructor_and_assignment) {
    List<int> a;
    a.push_back(10);
    a.push_back(20);
    List<int> b = a;
    ASSERT_EQUAL(b.size(), 2);
    vector<int> expected_b{10,20};
    vector<int> actual_b(b.begin(), b.end());
    ASSERT_SEQUENCE_EQUAL(expected_b, actual_b);

    a.pop_back();
    ASSERT_EQUAL(a.size(), 1);
    ASSERT_EQUAL(b.size(), 2);
    List<int> c;
    c = b;
    ASSERT_EQUAL(c.size(), 2);
    vector<int> expected_c{10,20};
    vector<int> actual_c(c.begin(), c.end());
    ASSERT_SEQUENCE_EQUAL(expected_c, actual_c);
}

TEST(test_iterator_traversal_and_sequence_equal) {
    List<int> lst;
    for (int i = 0; i < 6; ++i) lst.push_back(i);
    vector<int> expected{0,1,2,3,4,5};
    ASSERT_SEQUENCE_EQUAL(lst, expected);
}

TEST(test_iterator_increment_and_decrement) {
    List<int> lst;
    for (int i = 1; i <= 3; ++i) lst.push_back(i);
    auto it = lst.begin();
    ASSERT_EQUAL(*it, 1);
    ++it;
    ASSERT_EQUAL(*it, 2);
    it++;
    ASSERT_EQUAL(*it, 3);

    auto end_it = lst.end();
    --end_it;
    ASSERT_EQUAL(*end_it, 3);
    --end_it;
    ASSERT_EQUAL(*end_it, 2);
}

TEST(test_insert_and_erase_variants) {
    List<int> lst;
    lst.insert(lst.end(), 2);
    lst.insert(lst.begin(), 1);
    auto it = lst.begin(); ++it;
    lst.insert(it, 5);
    vector<int> expected_ins1{1,5,2};
    ASSERT_SEQUENCE_EQUAL(lst, expected_ins1);

   auto it_middle = lst.begin(); ++it_middle;
    auto it_after = lst.erase(it_middle);
    ASSERT_EQUAL(*it_after, 2);
    vector<int> expected_ins2{1,2};
    ASSERT_SEQUENCE_EQUAL(lst, expected_ins2);

    lst.erase(lst.begin());
    ASSERT_SEQUENCE_EQUAL(lst, vector<int>{2});

    auto it_end = lst.erase(lst.begin());
    ASSERT_TRUE(it_end == lst.end());
    ASSERT_TRUE(lst.empty());
}

TEST(test_iterator_dereference_and_arrow) {
    struct S { int v; };
    List<S> lst;
    lst.push_back(S{42});
    auto it = lst.begin();
    ASSERT_EQUAL(it->v, 42);
    ASSERT_EQUAL((*it).v, 42);
}

TEST(test_default_iterator_equal) {
    List<int>::Iterator a;
    List<int>::Iterator b;
    ASSERT_TRUE(a == b);

    List<int> lst;
    lst.push_back(1);
    auto list_it = lst.begin();
    ASSERT_TRUE(a != list_it);
}

TEST(test_insert_returns_iterator) {
    List<int> lst;
    lst.push_back(1);
    lst.push_back(3);
    auto it = lst.begin(); ++it;
    auto ret = lst.insert(it, 2);
    ASSERT_EQUAL(*ret, 2);
    auto check = lst.begin(); ++check;
    ASSERT_TRUE(ret == check);
}

TEST(test_erase_returns_end_when_erasing_last) {
    List<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);
    auto last = lst.end(); --last;
    auto ret = lst.erase(last);
    ASSERT_TRUE(ret == lst.end());
    ASSERT_EQUAL(lst.size(), 2);
    vector<int> expected{1,2};
    ASSERT_SEQUENCE_EQUAL(lst, expected);
}

TEST(test_self_assignment) {
    List<int> lst;
    for (int i = 0; i < 5; ++i) lst.push_back(i);
    vector<int> before(lst.begin(), lst.end());
    List<int>& alias = lst;
    lst = alias;
    vector<int> after(lst.begin(), lst.end());
    ASSERT_SEQUENCE_EQUAL(before, after);
}

TEST(test_iterators_same_location_equal) {
    List<int> lst;
    lst.push_back(10);
    lst.push_back(20);
    auto it1 = lst.begin();
    auto it2 = it1;
    ASSERT_TRUE(it1 == it2);
    ++it2; --it2;
    ASSERT_TRUE(it1 == it2);
}

TEST(test_copy_empty_and_large) {
    List<int> a;
    List<int> b = a;
    ASSERT_TRUE(b.empty());

    List<int> big;
    for (int i = 0; i < 50; ++i) big.push_back(i);
    List<int> bigcopy = big;
    vector<int> expected_big(big.begin(), big.end());
    vector<int> actual_big(bigcopy.begin(), bigcopy.end());
    ASSERT_SEQUENCE_EQUAL(expected_big, actual_big);
}

TEST(test_assignment_from_empty) {
    List<int> a;
    a.push_back(1);
    a.push_back(2);
    List<int> empty;
    a = empty;
    ASSERT_TRUE(a.empty());
    ASSERT_EQUAL(a.size(), 0);
    ASSERT_TRUE(a.begin() == a.end());
}

TEST(test_postfix_increment_and_decrement) {
    List<int> lst;
    for (int i = 1; i <= 3; ++i) lst.push_back(i);
    auto it = lst.begin();
    auto old = it++;
    ASSERT_EQUAL(*old, 1);
    ASSERT_EQUAL(*it, 2);

    auto old2 = it--;
    ASSERT_EQUAL(*old2, 2);
    ASSERT_EQUAL(*it, 1);
}

TEST(test_erase_until_empty) {
    List<int> lst;
    for (int i = 1; i <= 5; ++i) lst.push_back(i);
    ASSERT_EQUAL(lst.size(), 5);
    while (!lst.empty()) {
        lst.erase(lst.begin());
    }
    ASSERT_TRUE(lst.empty());
    ASSERT_TRUE(lst.begin() == lst.end());
}

TEST(test__inserts_and_erases) {
    List<int> lst;
    vector<int> expected;
    for (int i = 1; i <= 6; ++i) {
        lst.push_back(i);
        expected.push_back(i);
    }

    for (int i = 0; i < 4; ++i) {
        if (i % 2 == 0) {
            lst.insert(lst.begin(), 100 + i);
            expected.insert(expected.begin(), 100 + i);
        } else {
            lst.insert(lst.end(), 200 + i);
            expected.push_back(200 + i);
        }
    }

    for (int i = 0; i < 4; ++i) {
        if (i % 2 == 0) {
            lst.erase(lst.begin());
            expected.erase(expected.begin());
        } else {
            auto it = lst.end(); --it;
            lst.erase(it);
            expected.pop_back();
        }
    }

    ASSERT_SEQUENCE_EQUAL(lst, expected);
}

TEST(test_iterator_store) {
    List<int> lst;
    for (int i = 1; i <= 4; ++i) lst.push_back(i);
    auto it = lst.begin(); ++it;
    auto saved = it;

    lst.push_front(0);
    lst.push_back(5);

    ASSERT_EQUAL(*saved, 2);
}

TEST(test_assignment) {
    List<int> a;
    List<int> b;
    for (int i = 1; i <= 3; ++i) a.push_back(i);
    for (int i = 10; i <= 11; ++i) b.push_back(i);
    a = b;
    ASSERT_SEQUENCE_EQUAL(a, vector<int>(b.begin(), b.end()));
    b.pop_back();
    ASSERT_NOT_EQUAL(a.size(), b.size());
}

TEST(test_insert_and_erase_end) {
    List<int> lst;
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);
    lst.insert(lst.end(), 4);
    ASSERT_EQUAL(lst.back(), 4);

    auto last = lst.end(); --last;
    auto ret = lst.erase(last);
    ASSERT_TRUE(ret == lst.end());
    ASSERT_EQUAL(lst.back(), 3);
}

TEST(test_iterator_copy_and_assign) {
    List<int> lst;
    lst.push_back(10);
    lst.push_back(20);
    lst.push_back(30);
    
    List<int>::Iterator it1 = lst.begin();
    List<int>::Iterator it2 = it1;
    ASSERT_TRUE(it1 == it2);
    ASSERT_EQUAL(*it1, *it2);
    
    List<int>::Iterator it3;
    it3 = lst.begin();
    ASSERT_TRUE(it3 == it1);
    
    ++it1;
    ASSERT_EQUAL(*it1, 20);
    ASSERT_EQUAL(*it2, 10);
}

TEST(test_iterate_backwards_from_end) {
    List<int> lst;
    for (int i = 1; i <= 5; ++i) lst.push_back(i);
    
    auto it = lst.end();
    --it;
    ASSERT_EQUAL(*it, 5);
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

TEST(test_insert_and_erase_second) {
    List<int> lst;
    
    auto it = lst.insert(lst.begin(), 1);
    ASSERT_EQUAL(*it, 1);
    ASSERT_EQUAL(lst.size(), 1);
    
    it = lst.insert(lst.end(), 3);
    ASSERT_EQUAL(*it, 3);
    ASSERT_EQUAL(lst.size(), 2);
    
    it = lst.begin();
    ++it;
    it = lst.insert(it, 2);
    ASSERT_EQUAL(*it, 2);
    ASSERT_EQUAL(lst.size(), 3);
    
    vector<int> expected{1, 2, 3};
    ASSERT_SEQUENCE_EQUAL(lst, expected);
    
    it = lst.begin();
    ++it;
    it = lst.erase(it);
    ASSERT_EQUAL(*it, 3);
    ASSERT_EQUAL(lst.size(), 2);
    
    it = lst.erase(lst.begin());
    ASSERT_EQUAL(*it, 3);
    ASSERT_EQUAL(lst.size(), 1);
    
    it = lst.erase(lst.begin());
    ASSERT_TRUE(it == lst.end());
    ASSERT_TRUE(lst.empty());
}


TEST_MAIN()
