/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_system_creation.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstawski <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:33:45 by mstawski          #+#    #+#             */
/*   Updated: 2026/03/18 13:36:49 by mstawski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	ft_create_monitoring_system_thread(t_monitor *monitor)
{
	if (monitor->philosophers->data.philosophers_nb == 1)
		pthread_create(&monitor->thread, NULL,
			ft_monitoring_system_individual_plan, monitor);
	else
		pthread_create(&monitor->thread, NULL, ft_monitoring_system, monitor);
}

void	ft_create_monitoring_system(t_monitor *monitor, t_philo *philosophers)
{
	monitor->philosophers = philosophers;
	monitor->everyone_alive = 1;
	monitor->time_to_die = philosophers->data.time_to_die;
	monitor->time_to_eat = philosophers->data.time_to_eat;
	monitor->time_to_sleep = philosophers->data.time_to_sleep;
	monitor->times_to_eat = philosophers->data.times_to_eat;
	monitor->philosophers_nb = philosophers->data.philosophers_nb;
	monitor->stuffed_philosophers = 0;
}
