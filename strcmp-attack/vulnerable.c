#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/* This is a function pointer that prevents gcc from detecting a call to its
 * internal strcmp and doing crazy optimizations.
 *
 * This pointer is not static so gcc can't be sure that it is not changed by
 * someone from another object file and it will always be equal to `strcmp`.
 */
int (*my_strcmp)(const char *s1, const char *s2) = strcmp;

/* This function is based on examples from Optimization Manual by Intel:
 *    http://www.intel.com/content/dam/www/public/us/en/documents/white-papers/ia-32-ia-64-benchmark-code-execution-paper.pdf
 *
 * It uses CPUID instruction to ensure that the CPU doesn't reorder
 * instructions that precede the CPUID with ones that follow it.
 */
static inline uint64_t timestamp(void)
{
	uint32_t bottom;
	uint32_t top;
	asm volatile (
			"CPUID\n\t"
			"RDTSC\n\t"
			"mov %%edx, %0\n\t"
			"mov %%eax, %1\n\t": "=r" (top), "=r" (bottom)
#if __x86_64__
			:: "%rax", "%rbx", "%rcx", "%rdx");
#elif __i386__
			:: "%eax", "%ebx", "%ecx", "%edx");
#endif
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

	if (n <= 0)
		usage(argv[0]);

	begin = timestamp();
	for (int i = 0; i < n; ++i)
		trash += my_strcmp(argv[1], reference);
	end = timestamp();

	(void)trash;

	printf("%lld\n", end - begin);
}
