*This project has been created as part of the 42 curriculum by <login>.*

# get_next_line

## Description
**get_next_line** is a C programming project designed to re-create a function similar to the POSIX `getline()`. The main objective is to write a function that reads from a given file descriptor (or standard input) and returns a single line per call, ending with a newline character (`\n`) if one is present.

Calling `get_next_line()` in a loop allows reading the entire content of a file line-by-line, regardless of the buffer size used for reading. The project introduces low-level file I/O operations (`read`), static variable management across multiple function invocations, and precise dynamic memory handling (`malloc` / `free`) to guarantee zero memory leaks.

---

## Detailed Algorithm Explanation & Technical Choices

System calls like `read()` fetch data in fixed chunks of size `BUFFER_SIZE`, which rarely align with line boundaries (`\n`). To handle this smoothly across function calls, the implementation relies on a **Static Stash** mechanism.

The algorithm breaks down into three distinct steps:

1. **Reading & Stashing:**
   The function continuously calls `read()` with a buffer of size `BUFFER_SIZE`, appending the newly read characters onto a static string (`stash`). Reading continues until either:
   - A newline character (`\n`) is found inside `stash`.
   - `read()` returns `0` (End of File).
   - `read()` returns `-1` (Read error / bad file descriptor).

2. **Line Extraction:**
   Once a `\n` is detected (or EOF is hit with leftover bytes), memory is dynamically allocated specifically for the line up to and including the `\n` (or EOF termination). This newly allocated string is prepared to be returned to the caller.

3. **Stash Truncation & Cleaning:**
   The extracted line is removed from the static `stash`, leaving behind any remaining trailing characters for subsequent calls to `get_next_line()`. If no characters remain, or if an error occurs, `stash` is safely freed and set to `NULL` to prevent dangling pointers and memory leaks.

---

## Instructions

### Integration & Compilation

Include `get_next_line.h` in your source code and compile the C files along with your main program. You can define `BUFFER_SIZE` at compile time:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c -o gnl_demo

```

> **Note:** Overriding `BUFFER_SIZE` allows testing performance across different buffer values (e.g., `BUFFER_SIZE=1`, `BUFFER_SIZE=9999`, or `BUFFER_SIZE=10000000`).

### Usage Example

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("test.txt", O_RDONLY);
    if (fd < 0)
        return (1);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}

```
---
## Resources

### References & Documentation

* [Static Variables in C](https://www.geeksforgeeks.org/static-variables-in-c/) — Guide on scope and lifetime of static storage duration in C.
* [GeeksforGeeks: `getline()` function in C++](https://www.geeksforgeeks.org/cpp/getline-string-c/) — Overview of line-by-line input processing concepts.

### AI Usage

AI (Gemini) was utilized during the development of this project for the following specific tasks:

* **Documentation & README Structuring:** Assisting with layout, formatting, and drafting clear Markdown documentation compliant with 42 project submission guidelines.

* **Edge-Case Brainstorming:** Outlining edge cases during algorithm design (e.g., buffer size changes mid-execution, multiple consecutive `\n` characters, reading from `stdin`, and invalid file descriptors).

* **Code Review & Static Analysis:** Verifying edge-case `NULL` checks and ensuring proper `free()` operations on memory allocated for the static stash on error paths.