#include <stdio.h>
#include <pthread.h>

int balance = 0;
pthread_mutex_t lock;

void	*deposit(void *arg)
{
	int	i = 0;

	while (i < 1000000)
	{
		pthread_mutex_lock(&lock);
		balance++;
		pthread_mutex_unlock(&lock);
		i++;
	}
	return (NULL);
}

int	main(void)
{
	pthread_t thread1, thread2;

	pthread_mutex_init(&lock, NULL);

	pthread_create(&thread1, NULL, deposit, NULL);
	pthread_create(&thread2, NULL, deposit, NULL);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	pthread_mutex_destroy(&lock);
	printf("Oczekiwano: 2000000\n");
	printf("Stan konta: %d\n", balance);
	return (0);
}
