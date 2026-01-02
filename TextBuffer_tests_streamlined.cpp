#include "TextBuffer.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Streamlined comprehensive TextBuffer tests

TEST(test_constructor_and_getters) {
    TextBuffer tb;
    ASSERT_TRUE(tb.is_at_end());
    ASSERT_EQUAL(tb.size(), 0);
    ASSERT_EQUAL(tb.get_row(), 1);
    ASSERT_EQUAL(tb.get_column(), 0);
    ASSERT_EQUAL(tb.get_index(), 0);
}

TEST(test_insert_and_stringify) {
    TextBuffer tb;
    tb.insert('a');
    tb.insert('b');
    tb.insert('c');
    ASSERT_EQUAL(tb.size(), 3);
    ASSERT_EQUAL(tb.stringify(), string("abc"));
    ASSERT_EQUAL(tb.get_row(), 1);
    ASSERT_EQUAL(tb.get_column(), 3);
    ASSERT_EQUAL(tb.get_index(), 3);
    ASSERT_TRUE(tb.is_at_end());
}

TEST(test_insert_newline) {
    TextBuffer tb;
    tb.insert('a');
    tb.insert('\n');
    tb.insert('b');
    ASSERT_EQUAL(tb.stringify(), string("a\nb"));
    ASSERT_EQUAL(tb.get_row(), 2);
    ASSERT_EQUAL(tb.get_column(), 1);
    ASSERT_EQUAL(tb.get_index(), 3);
}

TEST(test_forward_and_backward) {
    TextBuffer tb;
    tb.insert('x');
    tb.insert('y');
    tb.insert('z');
    
    // At end: row=1, col=3
    ASSERT_TRUE(tb.is_at_end());
    
    // Move backward
    ASSERT_TRUE(tb.backward());
    ASSERT_EQUAL(tb.data_at_cursor(), 'z');
    ASSERT_EQUAL(tb.get_column(), 2);
    
    tb.backward();
    ASSERT_EQUAL(tb.data_at_cursor(), 'y');
    ASSERT_EQUAL(tb.get_column(), 1);
    
    tb.backward();
    ASSERT_EQUAL(tb.data_at_cursor(), 'x');
    ASSERT_EQUAL(tb.get_column(), 0);
    ASSERT_EQUAL(tb.get_index(), 0);
    
    // Cannot go before start
    ASSERT_FALSE(tb.backward());
    
    // Move forward
    tb.forward();
    ASSERT_EQUAL(tb.data_at_cursor(), 'y');
    ASSERT_EQUAL(tb.get_column(), 1);
}

TEST(test_forward_backward_across_newline) {
    TextBuffer tb;
    tb.insert('a');
    tb.insert('\n');
    tb.insert('b');
    
    // At end: row=2, col=1
    tb.backward(); // at 'b': row=2, col=0
    ASSERT_EQUAL(tb.get_row(), 2);
    ASSERT_EQUAL(tb.get_column(), 0);
    
    tb.backward(); // at '\n': row=1, col=1
    ASSERT_EQUAL(tb.get_row(), 1);
    ASSERT_EQUAL(tb.get_column(), 1);
    
    tb.backward(); // at 'a': row=1, col=0
    ASSERT_EQUAL(tb.get_row(), 1);
    ASSERT_EQUAL(tb.get_column(), 0);
    
    // Forward across newline
    tb.forward(); // at '\n'
    ASSERT_EQUAL(tb.get_row(), 1);
    tb.forward(); // at 'b'
    ASSERT_EQUAL(tb.get_row(), 2);
    ASSERT_EQUAL(tb.get_column(), 0);
}

TEST(test_remove_char_and_newline) {
    TextBuffer tb;
    tb.insert('a');
    tb.insert('b');
    tb.insert('c');
    
    // Remove from middle
    tb.backward();
    tb.backward();
    ASSERT_EQUAL(tb.data_at_cursor(), 'b');
    ASSERT_TRUE(tb.remove());
    ASSERT_EQUAL(tb.stringify(), string("ac"));
    ASSERT_EQUAL(tb.data_at_cursor(), 'c');
    
    // Remove newline
    TextBuffer tb2;
    tb2.insert('x');
    tb2.insert('\n');
    tb2.insert('y');
    tb2.backward();
    tb2.backward();
    ASSERT_EQUAL(tb2.data_at_cursor(), '\n');
    tb2.remove();
    ASSERT_EQUAL(tb2.stringify(), string("xy"));
    ASSERT_EQUAL(tb2.get_row(), 1);
}

TEST(test_move_to_row_start_and_end) {
    TextBuffer tb;
    tb.insert('a');
    tb.insert('b');
    tb.insert('c');
    
    tb.move_to_row_start();
    ASSERT_EQUAL(tb.get_column(), 0);
    ASSERT_EQUAL(tb.data_at_cursor(), 'a');
    
    tb.move_to_row_end();
    ASSERT_TRUE(tb.is_at_end());
    
    // With newline
    tb.move_to_row_start();
    tb.insert('\n');
    tb.move_to_row_start();
    ASSERT_EQUAL(tb.get_row(), 2);
    ASSERT_EQUAL(tb.get_column(), 0);
}

TEST(test_move_to_column) {
    TextBuffer tb;
    tb.insert('a');
    tb.insert('b');
    tb.insert('c');
    tb.insert('d');
    
    tb.move_to_row_start();
    tb.move_to_column(2);
    ASSERT_EQUAL(tb.get_column(), 2);
    ASSERT_EQUAL(tb.data_at_cursor(), 'c');
    
    // Move to column beyond row length
    tb.move_to_column(100);
    ASSERT_TRUE(tb.is_at_end());
}

TEST(test_up_and_down) {
    TextBuffer tb;
    tb.insert('a');
    tb.insert('b');
    tb.insert('c');
    tb.insert('\n');
    tb.insert('x');
    tb.insert('y');
    tb.insert('z');
    
    // At row 2, col 3
    ASSERT_EQUAL(tb.get_row(), 2);
    
    // Move up preserves column
    ASSERT_TRUE(tb.up());
    ASSERT_EQUAL(tb.get_row(), 1);
    ASSERT_EQUAL(tb.get_column(), 3);
    ASSERT_FALSE(tb.is_at_end()); // at index 3 (after 'c'), not at end of buffer
    
    // Cannot move up from row 1
    ASSERT_FALSE(tb.up());
    
    // Move down
    ASSERT_TRUE(tb.down());
    ASSERT_EQUAL(tb.get_row(), 2);
    ASSERT_EQUAL(tb.get_column(), 3);
    
    // Cannot move down from last row
    ASSERT_FALSE(tb.down());
}

TEST(test_up_down_with_different_row_lengths) {
    TextBuffer tb;
    tb.insert('1');
    tb.insert('2');
    tb.insert('3');
    tb.insert('4');
    tb.insert('5');
    tb.insert('\n');
    tb.insert('a');
    tb.insert('b');
    
    // At row 2, col 2
    ASSERT_EQUAL(tb.get_column(), 2);
    
    // Move up to longer row
    tb.up();
    ASSERT_EQUAL(tb.get_row(), 1);
    ASSERT_EQUAL(tb.get_column(), 2);
    ASSERT_EQUAL(tb.data_at_cursor(), '3');
    
    // Move to end of row 1
    tb.move_to_column(4);
    ASSERT_EQUAL(tb.data_at_cursor(), '5');
    
    // Move down - column clamped to row 2 length
    tb.down();
    ASSERT_EQUAL(tb.get_row(), 2);
    ASSERT_TRUE(tb.is_at_end()); // row 2 only has 2 chars
}

TEST(test_complex_editing) {
    TextBuffer tb;
    tb.insert('h');
    tb.insert('e');
    tb.insert('l');
    tb.insert('l');
    tb.insert('o');
    tb.insert('\n');
    tb.insert('w');
    tb.insert('o');
    tb.insert('r');
    tb.insert('l');
    tb.insert('d');
    
    ASSERT_EQUAL(tb.stringify(), string("hello\nworld"));
    ASSERT_EQUAL(tb.size(), 11);
    ASSERT_EQUAL(tb.get_row(), 2);
    ASSERT_EQUAL(tb.get_column(), 5);
    
    // Remove some characters
    tb.backward();
    tb.remove(); // remove 'd'
    ASSERT_EQUAL(tb.stringify(), string("hello\nworl"));
    
    // Navigate and insert
    tb.move_to_row_start(); // row 2, col 0, index 6
    tb.forward();           // row 2, col 1, index 7
    tb.insert('W');         // "hello\nwWorl", row 2, col 2, index 8
    ASSERT_EQUAL(tb.get_index(), 8);
}

TEST_MAIN()
