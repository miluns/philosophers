#include "../philosophers.h"

void	ft_monitoring_system_individual_plan(t_monitor *monitor)
{
	while (1)
	{
		if (get_time_in_ms() - monitor->philosophers->last_meal > (long)monitor->time_to_die) 
		{
			ft_safe_print(monitor->philosophers, "died");
			monitor->philosophers->is_alive = false;
			break ;
		}
		if (monitor->times_to_eat <= monitor->philosophers->data.eating_turns)
		{
			monitor->philosophers->is_alive = false;
			break ;
		}
	}
}

void	*ft_monitoring_system(void *arg)
{
	t_monitor	*monitor;

	monitor = (t_monitor *)arg;
	while (1)
	{
		if ((get_time_in_ms() - monitor->philosophers->last_meal) > (long)monitor->time_to_die) 
		{
			ft_safe_print(monitor->philosophers, "died");
			monitor->philosophers->is_alive = false;
			break ;
		}
		if (monitor->philosophers->data.eating_turns >= monitor->times_to_eat)
		{
			monitor->stuffed_philosopers++;
			if (monitor->stuffed_philosopers == monitor->number_of_philosophers)
				break ;
		}
		monitor->philosophers = monitor->philosophers->next;
	}
	return (NULL);
}

void	ft_create_monitoring_system(t_monitor *monitor, t_philo *philosophers)
{
	monitor->philosophers = philosophers;
	monitor->time_to_die = philosophers->data.time_to_die;
	monitor->time_to_eat = philosophers->data.time_to_eat;
	monitor->time_to_sleep = philosophers->data.time_to_sleep;
	monitor->times_to_eat = philosophers->data.times_to_eat;
	monitor->number_of_philosophers = philosophers->data.number_of_philosophers;
	monitor->stuffed_philosopers = 0;
}

void	ft_create_monitoring_system_thread(t_monitor *monitor)
{
	if (monitor->philosophers->data.nb_philo == 1)
		pthread_create(&monitor->thread, NULL, ft_monitoring_system_individual_plan, monitor);
	else	
		pthread_create(&monitor->thread, NULL, ft_monitoring_system, monitor);
}
