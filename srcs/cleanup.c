#include "../philosophers.h"

void	ft_cleanup(t_monitor *monitor, t_philo *philosophers, pthread_mutex_t *global_mutexes)
{
	pthread_mutex_destroy(&global_mutexes[0]);
	pthread_mutex_destroy(&global_mutexes[1]);
	pthread_join(monitor->thread, NULL);
	if (philosophers->data.number_of_philosophers == 1)
	{
		pthread_join(philosophers->thread, NULL);
		pthread_mutex_destroy(&philosophers->fork);
		pthread_mutex_destroy(&philosophers->eating);
		free(philosophers);
	}
	while (philosophers && philosophers->id != philosophers->data.number_of_philosophers)
		philosophers = philosophers->next;
	philosophers = philosophers->previous;
	while (philosophers && philosophers->id > 1)
	{
		pthread_join(philosophers->next->thread, NULL);
		pthread_mutex_destroy(&philosophers->next->fork);
		pthread_mutex_destroy(&philosophers->next->eating);
		free(philosophers->next);
		philosophers = philosophers->previous;
	}
	if (philosophers->id == 1)
	{
		pthread_join(philosophers->thread, NULL);
		pthread_mutex_destroy(&philosophers->fork);
		pthread_mutex_destroy(&philosophers->eating);
		free(philosophers);
	}
}
