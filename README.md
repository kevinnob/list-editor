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

# list-editor

A standalone, terminal-based text editor and supporting data-structure library implemented in
C++17. The project demonstrates low-level container design, iterator implementation, and an
editor abstraction built on top of a linked list of characters.

What this project does

- Implements a generic doubly-linked list container (`List<T>`) with a bidirectional iterator,
	deep-copy semantics, and proper memory management.
- Implements a cursor-based text buffer (`TextBuffer`) that stores characters in a linked list and
	provides editor operations: insert, remove, forward, backward, move-to-row/column, up, and down.
- Provides example frontends for testing and interaction: a scriptable `line` tool and two
	terminal visual frontends (`e0`, `femto`).
- Includes unit tests and streamlined test suites for both the list and the text buffer.

Highlights (skills & concepts demonstrated)

- Manual memory management (`new`/`delete`) and RAII.
- Implementation of the Big Three: copy constructor, copy assignment, destructor.
- Iterator design for a custom container (bidirectional traversal, iterator validity rules).
- Cursor-based editor semantics with row/column/index invariants and efficient updates.

Key files

- `List.hpp` — Doubly-linked list template with iterator and full API (push/pop, insert, erase).
- `TextBuffer.hpp`, `TextBuffer.cpp` — Editor abstraction that uses a linked list of characters.
- `line.cpp`, `e0.cpp`, `femto.cpp` — Scripted and interactive frontends for exercising the editor.
- `Makefile` — Build rules for tests and example programs.

Build and quick usage

Build everything (requires a C++17 compiler and make):

```bash
make -j4
```

Run the test suite:

```bash
make test
```

Run the scriptable `line` program (system tests):

```bash
./line.exe < line_test1.in > line_test1.out
diff -qB line_test1.out line_test1.out.correct
```

Run the interactive visual editor (may require `ncurses` on some systems):

```bash
make e0.exe
./e0.exe
```

Development tips

- Use AddressSanitizer and UndefinedBehaviorSanitizer while developing to detect memory errors:

```bash
c++ --std=c++17 -g -fsanitize=address,undefined TextBuffer.cpp TextBuffer_tests.cpp -o tb_test_san
./tb_test_san
```

- The `line` program is useful for deterministic regression tests; `e0` and `femto` are useful for
	interactive testing.

License

This repository contains student code and test materials; adapt and attribute appropriately if
reusing parts of it.

What this project does (detailed)

This project implements two core components that together provide a simple terminal text
editor: a low-level container (`List<T>`) and a higher-level editor abstraction (`TextBuffer`).
Below is a walkthrough of the main behaviors, invariants, and example sequences that illustrate
how the editor works.

1) `List<T>` (doubly-linked list)

- Structure: each node stores `datum`, `prev`, and `next`. The list keeps `first` and `last`
	pointers and a `list_size` counter.
- Iterators: the iterator stores the current node pointer and a pointer/reference to the owning
	`List<T>` so that an `end()` iterator can be decremented (it can find `last`). Iteration is
	bidirectional using `operator++`/`operator--`.
- Memory management: all node allocations use `new` and are freed with `delete` in the
	destructor. Copying performs a deep copy of nodes; assignment follows copy-and-swap or an
	equivalent safe pattern to avoid leaks.

2) `TextBuffer` (cursor-based editor)

- Underlying data: the buffer stores characters in a linked list (`List<char>` or `std::list<char>`).
- Cursor semantics:
	- The `cursor` member is an iterator that marks the insertion/deletion point.
	- Insertion writes the character immediately to the left of the cursor.
	- Removal deletes the character at the cursor (if `cursor == end()` there is nothing to remove).
	- The cursor may be set to `end()` allowing insertion at the end of the buffer.
- Position invariants:
	- `row` is 1-indexed: the first row is `row == 1`.
	- `column` is 0-indexed: at the start of a line `column == 0`.
	- `index` is the total number of characters from the start of the buffer to the cursor.
	- These invariants are updated incrementally on `forward()`, `backward()`, `insert()`, and
		`remove()`; `compute_column()` recomputes the column only when moving backward across a
		newline boundary (this keeps common operations O(1) while making occasional O(k) work, where
		k is the length of a single line).

Example editing session (visualized):

Start with empty buffer (cursor at `end()`):

	|  (cursor)  => row=1 column=0 index=0

Insert characters `a`, `b`, `c`:

	insert('a') -> buffer: a|  row=1 col=1 idx=1
	insert('b') -> ab|  row=1 col=2 idx=2
	insert('c') -> abc| row=1 col=3 idx=3

Insert newline `\n`:

	insert('\n') -> abc\n| row=2 col=0 idx=4

Insert `x`, `y` at start of second line:

	insert('x') -> abc\nx| row=2 col=1 idx=5
	insert('y') -> abc\nxy| row=2 col=2 idx=6

Move backward and remove `y`:

	backward() -> abc\nx| row=2 col=1 idx=5
	remove()   -> abc\nx| row=2 col=1 idx=5 (cursor points to what used to be after x)

3) Navigation (up/down/home/end)

- `move_to_row_start()` moves the cursor to column 0 of the current row.
- `move_to_row_end()` moves the cursor to the position after the last character of the row
	(stops at a newline or end()).
- `move_to_column(n)` attempts to set the column to `n` in the current row; if `n` is past the
	end of the row it will move to the row end.
- `up()` and `down()` attempt to move the cursor vertically while preserving the desired
	column when possible; behavior at variable-length rows uses `move_to_column` to clamp to the
	row length.

4) Guarantees and error handling

- All operations that cannot be performed (e.g., `backward()` at the start of the buffer or
	`up()` when already at the first row) return `false` and leave the buffer unchanged.
- The implementation is careful to maintain `row`, `column`, and `index` invariants so that
	getters like `get_row()`, `get_column()`, and `get_index()` always reflect the cursor's
	position.

Developer notes and tips

- Use the provided `line.cpp` and its test files to reproduce deterministic editing sequences for
	regression testing; the `e0` and `femto` visual editors are helpful for interactive testing.
- Use AddressSanitizer/UndefinedBehaviorSanitizer frequently while implementing or modifying
	`List.hpp` and `TextBuffer.cpp` to detect leaks and UB early.
- The autograder uses `std::list<char>` in some checks to decouple grading of `TextBuffer` from
	student `List` correctness; ensure your `TextBuffer` works with both implementations.


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

