#include "../philosophers.h"

void	*ft_monitoring_system_individual_plan(void *arg)
{
	t_monitor	*monitor;

	monitor = (t_monitor *)arg;
	usleep(50);
	while (1)
	{

		pthread_mutex_lock(&monitor->philosophers->eating);
		if (ft_get_time_in_ms() - monitor->philosophers->last_meal > (long)monitor->time_to_die) 
		{
			pthread_mutex_lock(&monitor->philosophers->death);
			ft_safe_print(monitor->philosophers, "died");
			monitor->everyone_alive = 0;
			pthread_mutex_unlock(&monitor->philosophers->death);
			pthread_mutex_unlock(&monitor->philosophers->eating);
			break ;
		}
		if (monitor->times_to_eat <= monitor->philosophers->data.eating_turns)
		{
			pthread_mutex_lock(&monitor->philosophers->death);
			monitor->philosophers->everyone_alive = 0;
			pthread_mutex_unlock(&monitor->philosophers->death);
			pthread_mutex_unlock(&monitor->philosophers->eating);
			break ;
		}
		pthread_mutex_unlock(&monitor->philosophers->eating);
		usleep(100);
	}
	return (NULL);
}

void	*ft_monitoring_system(void *arg)
{
	t_monitor	*monitor;

	monitor = (t_monitor *)arg;
	usleep(50);	
	while (1)
	{
		pthread_mutex_lock(&monitor->philosophers->eating);
		if ((ft_get_time_in_ms() - monitor->philosophers->last_meal) > (long)monitor->time_to_die) 
		{
			pthread_mutex_lock(&monitor->philosophers->death);
			monitor->everyone_alive = 0;
			ft_safe_print(monitor->philosophers, "died");
			pthread_mutex_unlock(&monitor->philosophers->death);
			pthread_mutex_unlock(&monitor->philosophers->eating);
			break ;
		}
		if (monitor->philosophers->data.eating_turns >= monitor->times_to_eat)
		{
			monitor->stuffed_philosophers++;
			if (monitor->stuffed_philosophers == monitor->number_of_philosophers)
			{
				pthread_mutex_lock(&monitor->philosophers->death);
				monitor->everyone_alive = 0;
				pthread_mutex_unlock(&monitor->philosophers->death);
				pthread_mutex_unlock(&monitor->philosophers->eating);
				break ;
			}
		}
		pthread_mutex_unlock(&monitor->philosophers->eating);
		monitor->philosophers = monitor->philosophers->next;
		usleep(100);
	}
	return (NULL);
}

void	ft_create_monitoring_system(t_monitor *monitor, t_philo *philosophers)
{
	monitor->philosophers = philosophers;
	monitor->everyone_alive = 1;
	monitor->time_to_die = philosophers->data.time_to_die;
	monitor->time_to_eat = philosophers->data.time_to_eat;
	monitor->time_to_sleep = philosophers->data.time_to_sleep;
	monitor->times_to_eat = philosophers->data.times_to_eat;
	monitor->number_of_philosophers = philosophers->data.number_of_philosophers;
	monitor->stuffed_philosophers = 0;
}

void	ft_create_monitoring_system_thread(t_monitor *monitor)
{
	if (monitor->philosophers->data.number_of_philosophers == 1)
		pthread_create(&monitor->thread, NULL, ft_monitoring_system_individual_plan, monitor);
	else	
		pthread_create(&monitor->thread, NULL, ft_monitoring_system, monitor);
}
