# list-editor

This repository contains an implementation for EECS 280 Project 5: Text Editor (list-editor).

What this project provides
- `List.hpp` — A doubly-linked list template with iterator support (Big Three implemented).
- `TextBuffer.cpp` / `TextBuffer.hpp` — A cursor-based text buffer built on a linked list.
- `line.cpp`, `e0.cpp`, `femto.cpp` — Small frontends and visual editors for manual testing.
- Unit tests: `List_tests.cpp`, `TextBuffer_tests.cpp` and streamlined test variants.

Build and test (macOS / Linux)
```bash
# Build the public and test executables (uses g++ / clang++)
make -j4

# Run all tests
make test

# Or build/run a single suite, e.g. List tests
make List_tests.exe && ./List_tests.exe
```

Run with sanitizers (recommended)
```bash
c++ --std=c++17 -g -fsanitize=address,undefined TextBuffer.cpp TextBuffer_tests.cpp -o tb_test_san && ./tb_test_san
```

Quick usage (interactive)
- `./line.exe` runs a non-visual line-based editor for quick scripted tests.
- `./e0.exe` or `./femto.exe` are terminal-based visual editors (may require `ncurses` for build).

Author & notes
- Repository owner: `kevinnob`
- Branch `complete-code` contains the finalized implementations and tests.
- This README was added and pushed to update the `main` branch with the completed project.

If you want me to open a pull request instead of merging directly into `main`, tell me and I will do that.
