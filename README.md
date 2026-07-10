# get_next_line tests

This workspace now includes `tests.c`, a small test runner for:

- `get_next_line`
- `safe_realoc`
- `ft_calloc`

The `get_next_line` tests check expected project behavior such as:

- returning `NULL` on empty input or invalid file descriptors
- keeping `\n` at the end of lines when present
- reading multiple lines in order
- handling a last line without a trailing newline
- handling long lines

## Build

```sh
cc -Wall -Wextra -Werror tests.c get_next_line.c get_next_line_utils.c -o tests_runner
```

## Run

```sh
./tests_runner
```

If some tests fail, the runner prints which behavior differs from the expected specification.