#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t	lock;

void	*counting(void *arg)
{
	int i;
	
	i = 0;
	while (i < 10)
	{
		if (!pthread_mutex_lock(&lock))
		{
			printf("%i\n", i);
			usleep(2500000);
			pthread_mutex_unlock(&lock);
			i++;
		}
		else
		{
			printf("Waiting...\n");
			i++;
		}
	}
}

int	main(void)
{
	pthread_t	thread1, thread2;
	
	pthread_mutex_init(&lock, NULL);

	pthread_create(&thread1, NULL, counting, NULL);
	pthread_create(&thread2, NULL, counting, NULL);
	
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	pthread_mutex_destroy(&lock);
}
