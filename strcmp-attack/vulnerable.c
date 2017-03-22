#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/* This function is based on similar function written by Bernstein. See
 * `../bernstein-attack-2005/server.c`.
 *
 * http://www.intel.com/content/dam/www/public/us/en/documents/white-papers/ia-32-ia-64-benchmark-code-execution-paper.pdf
 */
static inline uint64_t timestamp(void)
{
	uint32_t bottom;
	uint32_t top;
	asm volatile (".byte 15;.byte 49":"=a" (bottom), "=d"(top));
	return (((uint64_t) top) << 32) | bottom;
}

static void usage(const char *prog)
{
	printf(
		"NAME\n"
		"%1$s -- compare given string with \"aaaaaaa...\" multiple\n"
		"times and report total number of cycles.\n"
		"\n"
		"USAGE\n"
		"  %1$s <string> <iteration-number>\n"
		"\n", prog);
	exit(0);
}

/* 'a' is repeated 700 times */
char reference[] =
"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

int main(int argc, char **argv)
{
	uint64_t begin, end;
	int trash = 0;
	int n;

	if (argc != 3)
		usage(argv[0]);

	n = atoi(argv[2]);

	if (n < 0)
		usage(argv[0]);

	begin = timestamp();
	for (int i = 0; i < n; ++i)
		trash += strcmp(argv[1], reference);
	end = timestamp();

	printf("%lld\n", end - begin);
}
