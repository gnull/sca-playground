#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>

#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

static inline uint64_t timestamp(void)
{
	uint32_t bottom;
	uint32_t top;
	asm volatile (".byte 15;.byte 49":"=a" (bottom), "=d"(top));
	return (((uint64_t) top) << 32) | bottom;
}

static void usage(const char *prog)
{
	printf("%s program [arg1 [arg2 ...]]\n"
		"\n"
		"Execute program measuring number of CPU cycles it has been running.\n"
		"Program's stdout is redirected to /dev/null.\n",
		prog);
	exit(0);
}

/* TODO: Ensure that this process is being run always on the same CPU using
 * sched_setaffinity. If this condition does not hold, our measured time can be
 * messed up by scheduler.
 */

int main(int argc, char **argv)
{
	uint64_t begin, end;
	int err;
	int status;
	int null;
	int pid;
	int out;

	if (argc < 2)
		usage(argv[0]);

	null = open("/dev/null", O_WRONLY);
	assert(null != -1);

	/* STDOUT redirection level: God
	 *
	 * We redirect stdout before forking because otherwise it would be
	 * counted in time that we measure. */
	out = dup(1);
	err = dup2(null, 1);

	begin = timestamp();

	pid = vfork();
	if (pid == 0) {
		execv(argv[1], argv + 1);
		perror("execv");
		exit(1);
	} else if (pid < 0) {
		perror("vfork");
		exit(1);
	}

	/* Parent code follows */

	err = wait(&status);
	/* Get the timestamp as soon as we can */
	end = timestamp();
	/* And only then check return value */
	assert(err == pid);

	/* Now, restore the redirected stdout because we do not want to printf
	 * to /dev/null
	 */
	err = dup2(out, 1);
	assert(err != -1);

	printf("%lld\n", end - begin);

	return 0;
}
