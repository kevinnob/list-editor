#include "TextBuffer.hpp"
#include <iostream>
#include <string>
using namespace std;

int main() {
    // Test 1: up and down
    cout << "=== Test up and down ===" << endl;
    TextBuffer tb;
    tb.insert('a');
    tb.insert('b');
    tb.insert('c');
    tb.insert('\n');
    tb.insert('x');
    tb.insert('y');
    tb.insert('z');
    
    cout << "After insert: " << tb.stringify() << endl;
    cout << "Row: " << tb.get_row() << ", Col: " << tb.get_column() << endl;
    cout << "Index: " << tb.get_index() << ", at_end: " << tb.is_at_end() << endl;
    
    cout << "\nMoving up..." << endl;
    tb.up();
    cout << "Row: " << tb.get_row() << ", Col: " << tb.get_column() << endl;
    cout << "Index: " << tb.get_index() << ", at_end: " << tb.is_at_end() << endl;
    
    // Test 2: complex editing
    cout << "\n=== Test complex editing ===" << endl;
    TextBuffer tb2;
    tb2.insert('h'); tb2.insert('e'); tb2.insert('l'); tb2.insert('l'); tb2.insert('o');
    tb2.insert('\n');
    tb2.insert('w'); tb2.insert('o'); tb2.insert('r'); tb2.insert('l'); tb2.insert('d');
    
    cout << "After insert: " << tb2.stringify() << endl;
    cout << "Row: " << tb2.get_row() << ", Col: " << tb2.get_column() << endl;
    
    tb2.backward(); // move back from 'd'
    cout << "\nAfter backward:" << endl;
    cout << "Row: " << tb2.get_row() << ", Col: " << tb2.get_column() << endl;
    cout << "Index: " << tb2.get_index() << endl;
    
    tb2.remove(); // remove 'd'
    cout << "\nAfter remove 'd': " << tb2.stringify() << endl;
    cout << "Row: " << tb2.get_row() << ", Col: " << tb2.get_column() << endl;
    cout << "Index: " << tb2.get_index() << endl;
    
    tb2.move_to_row_start();
    cout << "\nAfter move_to_row_start:" << endl;
    cout << "Row: " << tb2.get_row() << ", Col: " << tb2.get_column() << endl;
    cout << "Index: " << tb2.get_index() << endl;
    
    tb2.forward();
    cout << "\nAfter forward:" << endl;
    cout << "Row: " << tb2.get_row() << ", Col: " << tb2.get_column() << endl;
    cout << "Index: " << tb2.get_index() << endl;
    
    tb2.insert('W');
    cout << "\nAfter insert 'W': " << tb2.stringify() << endl;
    cout << "Row: " << tb2.get_row() << ", Col: " << tb2.get_column() << endl;
    cout << "Index: " << tb2.get_index() << endl;
}
