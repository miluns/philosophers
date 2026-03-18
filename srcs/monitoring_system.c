/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_system.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstawski <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:33:15 by mstawski          #+#    #+#             */
/*   Updated: 2026/03/18 14:00:06 by mstawski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

bool	ft_philosophers_death_check(t_monitor *monitor)
{
	monitor->time_to_die = (long)monitor->time_to_die;
	pthread_mutex_lock(&monitor->philosophers->eating);
	if ((ft_get_time_in_ms() - monitor->philosophers->last_meal)
		> monitor->time_to_die)
	{
		pthread_mutex_lock(monitor->philosophers->death);
		monitor->everyone_alive = 0;
		ft_safe_print_monitor(monitor->philosophers, "died");
		pthread_mutex_unlock(monitor->philosophers->death);
		pthread_mutex_unlock(&monitor->philosophers->eating);
		return (true);
	}
	pthread_mutex_unlock(&monitor->philosophers->eating);
	return (false);
}

bool	ft_philosophers_meals_check(t_monitor *monitor)
{
	if (monitor->times_to_eat > 0)
	{
		pthread_mutex_lock(&monitor->philosophers->eating);
		if (monitor->philosophers->data.eating_turns == monitor->times_to_eat)
		{
			if (!monitor->philosophers->stuffed)
				monitor->stuffed_philosophers++;
			monitor->philosophers->stuffed = 1;
			if (monitor->stuffed_philosophers == monitor->philosophers_nb)
			{
				pthread_mutex_lock(monitor->philosophers->death);
				monitor->everyone_alive = 0;
				pthread_mutex_unlock(monitor->philosophers->death);
				pthread_mutex_unlock(&monitor->philosophers->eating);
				return (true);
			}
		}
		pthread_mutex_unlock(&monitor->philosophers->eating);
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
			break ;
		if (monitor->times_to_eat > 0)
			if (ft_philosophers_meals_check(monitor))
				break ;
		monitor->philosophers = monitor->philosophers->next;
		usleep(100);
	}
	return (NULL);
}
