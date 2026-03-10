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
	sum = ((long)tv.tv_sec * 1000 + (double)tv.tv_usec) / 1000;
	printf("CORRECT: %.3f \n", sum);
}
