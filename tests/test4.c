#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int	main(void)
{
	struct timeval start, end;
	long seconds, microseconds;
	double elapsed;

	gettimeofday(&start, NULL);
	
	printf("Przetwarzanie...\n");
	sleep(2);
	gettimeofday(&end, NULL);
	
	seconds = end.tv_sec - start.tv_sec;
	microseconds = end.tv_usec - start.tv_usec;
	
	elapsed = seconds + microseconds * 1e-6;
	
	printf("Czas wykonania w sekundach: %ld sekund\n", seconds);
	printf("Czas wykonania w microsekundach: %ld mikrosekund\n", microseconds);
	printf("Czas wykonania: %.6f sekund\n", elapsed);
	return (0);
}
