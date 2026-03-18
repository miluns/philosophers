/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_system.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstawski <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:33:15 by mstawski          #+#    #+#             */
/*   Updated: 2026/03/18 21:55:18 by mstawski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	ft_update_death_flag(t_monitor *monitor, t_philo *philosopher)
{
	pthread_mutex_lock(philosopher->death);
	monitor->everyone_alive = 0;
	pthread_mutex_unlock(philosopher->death);
	pthread_mutex_unlock(&philosopher->eating);
}

bool	ft_philosophers_death_check(t_monitor *monitor)
{
	t_philo	*philosophers;
	int		i;

	philosophers = monitor->philosophers;
	i = 0;
	while (i < monitor->philosophers_nb)
	{
		pthread_mutex_lock(&philosophers->eating);
		if ((ft_get_time_in_ms() - philosophers->last_meal)
			> (long)monitor->time_to_die)
		{
			pthread_mutex_lock(philosophers->death);
			monitor->everyone_alive = 0;
			ft_safe_print_monitor(philosophers, "died");
			pthread_mutex_unlock(philosophers->death);
			pthread_mutex_unlock(&philosophers->eating);
			return (true);
		}
		pthread_mutex_unlock(&philosophers->eating);
		philosophers = philosophers->next;
		i++;
	}
	return (false);
}

bool	ft_philosophers_meals_check(t_monitor *monitor)
{
	t_philo	*philosophers;
	int		i;

	philosophers = monitor->philosophers;
	i = 0;
	while (i < monitor->philosophers_nb)
	{
		pthread_mutex_lock(&philosophers->eating);
		if (philosophers->data.eating_turns == monitor->times_to_eat)
		{
			if (!philosophers->stuffed)
				monitor->stuffed_philosophers++;
			philosophers->stuffed = 1;
			if (monitor->stuffed_philosophers == monitor->philosophers_nb)
				return (ft_update_death_flag(monitor, philosophers), true);
		}
		pthread_mutex_unlock(&philosophers->eating);
		philosophers = philosophers->next;
		i++;
	}
	return (false);
}

void	*ft_monitoring_system_individual_plan(void *arg)
{
	t_monitor	*monitor;

	monitor = (t_monitor *)arg;
	ft_usleep(100);
	while (1)
	{
		if (ft_philosophers_death_check(monitor))
			break ;
		usleep(100);
	}
	return (NULL);
}

void	*ft_monitoring_system(void *arg)
{
	t_monitor	*monitor;

	monitor = (t_monitor *)arg;
	ft_usleep(100);
	while (1)
	{
		if (ft_philosophers_death_check(monitor))
			return (NULL);
		if (monitor->times_to_eat > 0)
			if (ft_philosophers_meals_check(monitor))
				return (NULL);
		monitor->philosophers = monitor->philosophers->next;
		usleep(100);
	}
}
