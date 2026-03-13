#include "../philosophers.h"

void	ft_thread_joining(t_monitor *monitor, t_philo *philosopers)
{
	int	i;

	pthread_join(monitor->thread, NULL);
	i = 0;
	while (i < philosopers->data.number_of_philosophers)
	{
		pthread_join(philosopers->thread, NULL);
		i++;
	}
}

void	ft_cleanup(t_philo *philosophers)
{
	while (philosophers && philosophers->id != philosophers->data.number_of_philosophers)
		philosophers = philosophers->next;
	philosophers = philosophers->previous;
	while (philosophers && philosophers->id > 1)
	{
		pthread_join(philosophers->next->thread, NULL);
		pthread_mutex_destroy(&philosophers->next->fork);
		free(philosophers->next);
		philosophers = philosophers->previous;
	}
	if (philosophers->id == 1)
	{
		pthread_join(philosophers->thread, NULL);
		pthread_mutex_destroy(&philosophers->fork);
		free(philosophers);
	}
}
