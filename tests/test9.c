#include <sys/time.h>
#include <stdio.h>

int	main(void)
{
	struct timeval	time;
	
	gettimeofday(&time, NULL);
	printf("%ld	%.6f\n", (time.tv_sec * 1000 + time.tv_usec / 1000), (time.tv_sec * 1000 + time.tv_usec / 1000));
}
