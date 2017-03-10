#include <stdio.h>
#include <stdint.h>

static inline uint64_t timestamp(void)
{
	uint32_t bottom;
	uint32_t top;
	asm volatile (".byte 15;.byte 49":"=a" (bottom), "=d"(top));
	return (((uint64_t) top) << 32) | bottom;
}

int main()
{
	printf("%lld\n", timestamp());
}
