#include "../philosophers.h"

void	ft_thread_cleanup(t_monitor *monitor, t_philo *philosophers)
{
	pthread_join(monitor->thread, NULL);
	if (philosophers->data.number_of_philosophers == 1)
	{
		pthread_join(philosophers->thread, NULL);
		return ;
	}
	while (philosophers && philosophers->id != philosophers->data.number_of_philosophers)
		philosophers = philosophers->next;
	philosophers = philosophers->previous;
	while (philosophers && philosophers->id > 1)
	{
		pthread_join(philosophers->next->thread, NULL);
		philosophers = philosophers->previous;
	}
	if (philosophers->id == 1)
	{	
		pthread_join(philosophers->next->thread, NULL);
		pthread_join(philosophers->thread, NULL);
	}
}

void	ft_mutexes_cleanup(t_monitor *monitor, t_philo *philosophers, pthread_mutex_t *global_mutexes)
{
	if (monitor->number_of_philosophers == 1)
	{
		pthread_mutex_destroy(&philosophers->fork);
		pthread_mutex_destroy(&philosophers->eating);
	}
	else
	{
		while (philosophers && philosophers->id != philosophers->data.number_of_philosophers)
			philosophers = philosophers->next;
		philosophers = philosophers->previous;
		while (philosophers && philosophers->id > 1)
		{
			pthread_mutex_destroy(&philosophers->next->fork);
			pthread_mutex_destroy(&philosophers->next->eating);
			philosophers = philosophers->previous;
		}
		if (philosophers->id == 1)
		{	
			pthread_mutex_destroy(&philosophers->next->fork);
			pthread_mutex_destroy(&philosophers->next->eating);
			pthread_mutex_destroy(&philosophers->fork);
			pthread_mutex_destroy(&philosophers->eating);
		}
	}
	pthread_mutex_destroy(&global_mutexes[0]);
	pthread_mutex_destroy(&global_mutexes[1]);
}

void	ft_memory_cleanup(t_monitor *monitor, t_philo *philosophers)
{
	free(monitor);
	if (philosophers->data.number_of_philosophers == 1)
		free(philosophers);	
	else
	{
		while (philosophers && philosophers->id != philosophers->data.number_of_philosophers)
			philosophers = philosophers->next;
		philosophers = philosophers->previous;
		while (philosophers && philosophers->id > 1)
		{
			free(philosophers->next);
			philosophers = philosophers->previous;
		}
		if (philosophers->id == 1)
		{	
			free(philosophers->next);
			free(philosophers);
		}
	}
}

void	ft_cleanup(t_monitor *monitor, t_philo *philosophers, pthread_mutex_t *global_mutexes)
{
	ft_thread_cleanup(monitor, philosophers);
	ft_mutexes_cleanup(monitor, philosophers, global_mutexes);
	ft_memory_cleanup(monitor, philosophers);
}