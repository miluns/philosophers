#include <sys/time.h>
#include <stdio.h>
#include <stddef.h>

int	main(void)
{
	struct timeval tv;
	double	sum;
	gettimeofday(&tv, NULL);
	printf("%ld\n", (long)tv.tv_sec);
	printf("%ld\n", (long)tv.tv_usec);
	sum = ((long)tv.tv_sec + (long)tv.tv_usec) * 1e-3;
	printf("CORRECT: %.3f \n", sum);
}
