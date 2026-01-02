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

# list-editor — EECS 280 Project 5: Text Editor

This repository contains a student implementation for EECS 280 Project 5 (Text Editor). The
project teaches Container ADTs, dynamic memory, the Big Three, doubly-linked lists, and
iterators by building a small terminal-editable text buffer backed by a doubly-linked list.

Project goals

- Implement a doubly-linked, double-ended `List<T>` with a bidirectional iterator and correct
	memory management (Big Three).
- Implement a `TextBuffer` that uses a linked list of characters (either the student `List<char>`
	or `std::list<char>`) and provides cursor-based editing with row/column/index tracking.
- Provide unit tests and small frontends (`line`, `e0`, `femto`) to validate and interact with the
	buffer.

Key files

- `List.hpp` — Templated doubly-linked list implementation with iterator support.
- `TextBuffer.hpp`, `TextBuffer.cpp` — TextBuffer interface and implementation.
- `List_public_tests.cpp`, `List_tests.cpp`, `List_tests_streamlined.cpp` — List test suites.
- `TextBuffer_public_tests.cpp`, `TextBuffer_tests.cpp`, `TextBuffer_tests_streamlined.cpp` —
	TextBuffer tests.
- `line.cpp`, `e0.cpp`, `femto.cpp` — Scriptable and visual frontends for the editor.
- `Makefile` — Build rules for tests and example programs.

Overview of design

- Cursor semantics: insertions insert to the left of the cursor; deletes remove at the cursor. The
	cursor can equal `end()` to allow insertion at the end.
- Rows and columns: `TextBuffer` tracks `row` (1-indexed) and `column` (0-indexed). `index` is the
	character offset from the start. `compute_column()` recomputes the column only when necessary
	(for example when moving backward across a newline).
- Performance: `List<T>` stores a `list_size` integer so `size()` is O(1) rather than O(n).

Build & test

1. Build everything (requires a C++17 compiler and `make`):

```bash
make -j4
```

2. Run the full test suite:

```bash
make test
```

3. Run a single test binary (examples):

```bash
make List_tests.exe && ./List_tests.exe
make TextBuffer_tests.exe && ./TextBuffer_tests.exe
```

Sanitizers (highly recommended while developing)

```bash
c++ --std=c++17 -g -fsanitize=address,undefined TextBuffer.cpp TextBuffer_tests.cpp -o tb_test_san
./tb_test_san
```

Interactive testing and visual editors

- `./line.exe` runs a simple linear interface. Two input files (`line_test1.in`, `line_test2.in`)
	are provided with expected outputs (`.out.correct`). Use `diff -qB` to compare.
- `./e0.exe` and `./femto.exe` are terminal-based editors. On macOS you may need `ncurses`:

```bash
brew install ncurses
```

System tests for `line`:

```bash
./line.exe < line_test1.in > line_test1.out
diff -qB line_test1.out line_test1.out.correct

./line.exe < line_test2.in > line_test2.out
diff -qB line_test2.out line_test2.out.correct
```

Autograder and submission

Submit the following files to the autograder:

- `List.hpp`
- `List_tests.cpp`
- `TextBuffer.cpp`

Autograder notes:

- The autograder runs your `List` unit tests against a collection of intentionally buggy solutions.
	Tests that pass on the correct implementation and fail on buggy solutions earn points. Make sure
	your tests are valid (they should pass with the correct implementation).
- Test suite restrictions: the autograder expects a single test file to contain at most 50
	`TEST()` items and to complete quickly (under 5 seconds).

Rules and guidelines

DO:
- Modify `.cpp` files and `List.hpp` only.
- Keep helper functions private within `List`.
- Use `std::string` for string work and pass large objects by const reference.
- Use sanitizers to check for memory issues.

DO NOT:
- Change public function signatures in `List.hpp` or `TextBuffer.hpp`.
- Use STL containers in your `List` implementation.
- Use C-style strings instead of `std::string`.

CI and next steps

If you want Continuous Integration, I can add a GitHub Actions workflow that builds and runs the
test suite on every push and reports failures.

Author

- Repository owner: `kevinnob` — student submission for EECS 280 Project 5.
