# List Editor — C++ Text Editor & Data Structures

A standalone, terminal-based text editor and supporting data-structure library implemented in **C++17**.  
This project demonstrates **low-level container design**, **iterator implementation**, and a **cursor-based editor abstraction** built on a doubly-linked list.

---

## Overview

The project is composed of two core components:

1. **`List<T>`** — a generic doubly-linked list with full iterator support and correct copy semantics  
2. **`TextBuffer`** — a cursor-based text buffer built on a linked list of characters

Together, these components form a minimal but fully functional text editor with both scripted and interactive frontends.

---

## Key Features

- Custom **doubly-linked list** implementation with:
  - Bidirectional iterators
  - Deep-copy semantics (Big Three)
  - Manual memory management
- **Cursor-based text buffer** supporting:
  - Insert / remove
  - Forward / backward navigation
  - Row & column movement (up, down, line start/end)
- Multiple frontends:
  - Scriptable line editor for deterministic testing
  - Terminal-based visual editors for interactive use
- Comprehensive **unit tests** for both data structures and editor behavior

---

## Technical Highlights

- Manual memory management using `new` / `delete` with RAII discipline  
- Implementation of the **Big Three** (copy constructor, copy assignment, destructor)  
- Custom **bidirectional iterator** design and validity rules  
- Efficient maintenance of cursor **row / column / index invariants**  
- Defensive programming with clear failure modes for invalid operations  

---

## Project Structure

```
.
├── List.hpp                 # Doubly-linked list template + iterator
├── TextBuffer.hpp/.cpp      # Cursor-based editor abstraction
├── line.cpp                 # Scriptable editor frontend
├── e0.cpp / femto.cpp       # Interactive terminal editors
├── List_tests.cpp           # Unit tests for List<T>
├── TextBuffer_tests.cpp     # Unit tests for TextBuffer
├── Makefile
```

---

## Build & Test

### Build everything
```bash
make -j4
```

### Run all tests
```bash
make test
```

### Run a single test suite
```bash
make List_tests.exe && ./List_tests.exe
make TextBuffer_tests.exe && ./TextBuffer_tests.exe
```

---

## Interactive Usage

### Scripted editor
```bash
./line.exe < line_test1.in > out.txt
```

### Visual editor (may require ncurses)
```bash
make e0.exe
./e0.exe
```

On macOS:
```bash
brew install ncurses
```

---

## Debugging & Sanitizers (Recommended)

```bash
c++ --std=c++17 -g -fsanitize=address,undefined \
TextBuffer.cpp TextBuffer_tests.cpp -o tb_test_san

./tb_test_san
```

---

## Why This Project Matters

This project focuses on **systems-level fundamentals** that are often hidden by high-level libraries:

- Ownership & lifetime management
- Iterator correctness
- Abstraction boundaries
- Testing against buggy implementations
- Reasoning about invariants under mutation

These skills translate directly to **C++ systems programming**, **performance-critical code**, and **low-level software engineering**.

---

## Notes

- The editor abstraction is intentionally minimal to emphasize correctness over features.
- The `TextBuffer` implementation is compatible with both the custom `List<T>` and `std::list<char>`, enabling independent testing of each component.
- Designed to be extended (e.g., file I/O, undo/redo, richer UI).

