#include "TextBuffer.hpp"

TextBuffer::TextBuffer()
  : data(), cursor(data.end()), row(1), column(0), index(0)
{}


bool TextBuffer::forward() {
    
    if(cursor == data.end()){
        return false;
    }
    
    char oldChar = *cursor;
    cursor++;
    index++;

    if(oldChar == '\n'){
        column = 0;
        row++;
    }
    else{
        column++;
    }

    return true; 
    
}

bool TextBuffer::backward() {
    if(cursor == data.begin()){
        return false;
    }
    cursor--;
    index--;
    if(*cursor == '\n'){
        row--;
        column = compute_column();
    }
    else{
        column--;
    }
    return true;
    

}

void TextBuffer::insert(char c) {
    data.insert(cursor, c);
    index++;
    
    if(c == '\n'){
        row++;
        column = 0;
    }
    else{
        column++;
    }


}

bool TextBuffer::remove() {
    if(cursor == data.end()) return false;
    cursor = data.erase(cursor);
    return true;

}

void TextBuffer::move_to_row_start() {
    while(column != 0){
        backward();
    }

}

void TextBuffer::move_to_row_end() {
    while(cursor != data.end() && *cursor != '\n'){
        forward();
    }

}

void TextBuffer::move_to_column(int new_column){
    if(new_column < 0){
        new_column = 0;
    }
    if(new_column > column){
        while(cursor != data.end() && column < new_column && *cursor != '\n'){
            forward();
        }
    }
    else{
        while(column > 0 && column > new_column){
            backward();
        }

    }

}

bool TextBuffer::up() {
    if(row == 1){
        return false;
    }
    int moveCol = column;
    move_to_row_start();
    if(cursor != data.begin()){
        backward();
    }
    move_to_row_start();
    move_to_column(moveCol);
    return true;

}

bool TextBuffer::down(){
    int moveCol = column;
    move_to_row_end();
    if(cursor == data.end() || *cursor != '\n'){
        return false;
    }
    
    forward();
    move_to_column(moveCol);
    return true;
}

bool TextBuffer::is_at_end() const{
    return cursor == data.end();
}

char TextBuffer::data_at_cursor() const{
    return *cursor;
}

int TextBuffer::get_row() const{
    return row;
}

int TextBuffer::get_column() const{
    return column;
}

int TextBuffer::get_index() const{
    return index;
}
int TextBuffer::size() const{
    return data.size();
}

std::string TextBuffer::stringify() const{
    std::string s = "";
    for(auto it = data.begin(); it != data.end(); it++){
        s+=*it;
    }
    return s;
}
int TextBuffer::compute_column() const{
    Iterator it = cursor;
    int count = 0;

    if(data.empty()) return 0;

    if(it == data.end()){
        it--;
    }

    while(it != data.begin()){
        it--;
        if(*it == '\n'){
            break;
        }
        count++;
    }
    return count;
}

