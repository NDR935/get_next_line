#include "../get_next_line.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct s_test_stats
{
	int	passed;
	int	failed;
}t_test_stats;

static void	report_result(t_test_stats *stats, const char *name, int passed,
		const char *details)
{
	if (passed)
	{
		stats->passed++;
		printf("[PASS] %s\n", name);
	}
	else
	{
		stats->failed++;
		printf("[FAIL] %s: %s\n", name, details);
	}
}

static int	string_equals(const char *left, const char *right)
{
	if (left == NULL || right == NULL)
		return (left == right);
	return (strcmp(left, right) == 0);
}

static int	build_read_fd_from_string(const char *content)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
		return (-1);
	if (content != NULL)
		write(pipefd[1], content, strlen(content));
	close(pipefd[1]);
	return (pipefd[0]);
}

static void	test_ft_calloc_zero_initializes(t_test_stats *stats)
{
	char	*buffer;

	buffer = ft_calloc(8);
	report_result(stats, "ft_calloc returns allocated buffer", buffer != NULL,
		"expected non-NULL pointer");
	if (buffer == NULL)
		return ;
	report_result(stats, "ft_calloc zero-terminates first byte", buffer[0] == '\0',
		"expected first byte to be null terminator");
	free(buffer);
}

static void	test_safe_realoc_preserves_content(t_test_stats *stats)
{
	char	*buffer;

	buffer = ft_calloc(4);
	if (buffer == NULL)
	{
		report_result(stats, "safe_realoc grow setup", 0,
			"ft_calloc returned NULL");
		return ;
	}
	strcpy(buffer, "abc");
	safe_realoc(&buffer, 10);
	report_result(stats, "safe_realoc keeps content when growing",
		buffer != NULL && string_equals(buffer, "abc"),
		"expected reallocated string to preserve existing content");
	free(buffer);
}

static void	test_safe_realoc_truncates_safely(t_test_stats *stats)
{
	char	*buffer;

	buffer = ft_calloc(7);
	if (buffer == NULL)
	{
		report_result(stats, "safe_realoc shrink setup", 0,
			"ft_calloc returned NULL");
		return ;
	}
	strcpy(buffer, "abcdef");
	safe_realoc(&buffer, 4);
	report_result(stats, "safe_realoc truncates and terminates when shrinking",
		buffer != NULL && string_equals(buffer, "abc"),
		"expected shrunk string to be \"abc\"");
	free(buffer);
}

static void	test_gnl_empty_input_returns_null(t_test_stats *stats)
{
	int		fd;
	char	*line;

	fd = build_read_fd_from_string("");
	line = get_next_line(fd);
	report_result(stats, "get_next_line returns NULL on empty input", line == NULL,
		"expected NULL when no bytes are available");
	free(line);
	close(fd);
}

static void	test_gnl_single_line_with_newline(t_test_stats *stats)
{
	int		fd;
	char	*line;

	fd = build_read_fd_from_string("hello\n");
	line = get_next_line(fd);
	report_result(stats, "get_next_line includes trailing newline",
		string_equals(line, "hello\n"),
		"expected returned line to include newline character");
	free(line);
	close(fd);
}

static void	test_gnl_last_line_without_newline(t_test_stats *stats)
{
	int		fd;
	char	*line;

	fd = build_read_fd_from_string("final line");
	line = get_next_line(fd);
	report_result(stats, "get_next_line returns last line without newline",
		string_equals(line, "final line"),
		"expected last line to be returned as-is");
	free(line);
	close(fd);
}

static void	test_gnl_reads_multiple_lines_sequentially(t_test_stats *stats)
{
	int		fd;
	char	*first;
	char	*second;
	char	*third;

	fd = build_read_fd_from_string("one\ntwo\nthree");
	first = get_next_line(fd);
	second = get_next_line(fd);
	third = get_next_line(fd);
	report_result(stats, "get_next_line reads first line correctly",
		string_equals(first, "one\n"), "expected first line to be \"one\\n\"");
	report_result(stats, "get_next_line reads second line correctly",
		string_equals(second, "two\n"), "expected second line to be \"two\\n\"");
	report_result(stats, "get_next_line reads final line correctly",
		string_equals(third, "three"), "expected third line to be \"three\"");
	free(first);
	free(second);
	free(third);
	close(fd);
}

static void	test_gnl_invalid_fd_returns_null(t_test_stats *stats)
{
	char	*line;

	line = get_next_line(-1);
	report_result(stats, "get_next_line returns NULL for invalid fd", line == NULL,
		"expected NULL for invalid file descriptor");
	free(line);
}

static void	test_gnl_long_line(t_test_stats *stats)
{
	char	input[257];
	char	expected[258];
	int		index;
	int		fd;
	char	*line;

	index = 0;
	while (index < 256)
	{
		input[index] = 'a' + (index % 26);
		expected[index] = input[index];
		index++;
	}
	input[index] = '\n';
	input[index + 1] = '\0';
	expected[index] = '\n';
	expected[index + 1] = '\0';
	fd = build_read_fd_from_string(input);
	line = get_next_line(fd);
	report_result(stats, "get_next_line handles long lines",
		string_equals(line, expected),
		"expected long line to be returned intact with newline");
	free(line);
	close(fd);
}

int	main(void)
{
	t_test_stats	stats;

	stats.passed = 0;
	stats.failed = 0;
	test_ft_calloc_zero_initializes(&stats);
	test_safe_realoc_preserves_content(&stats);
	test_safe_realoc_truncates_safely(&stats);
	test_gnl_empty_input_returns_null(&stats);
	test_gnl_single_line_with_newline(&stats);
	test_gnl_last_line_without_newline(&stats);
	test_gnl_reads_multiple_lines_sequentially(&stats);
	test_gnl_invalid_fd_returns_null(&stats);
	test_gnl_long_line(&stats);
	printf("\nSummary: %d passed, %d failed\n", stats.passed, stats.failed);
	if (stats.failed != 0)
		return (1);
	return (0);
}