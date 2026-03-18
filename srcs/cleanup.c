/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstawski <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:32:45 by mstawski          #+#    #+#             */
/*   Updated: 2026/03/18 13:49:02 by mstawski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	ft_thread_cleanup(t_monitor *monitor, t_philo *philosophers)
{
	pthread_join(monitor->thread, NULL);
	if (philosophers->data.philosophers_nb == 1)
	{
		pthread_join(philosophers->thread, NULL);
		return ;
	}
	while (philosophers
		&& philosophers->id != philosophers->data.philosophers_nb)
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

void	ft_destroy_mutexes(t_philo *philosopher)
{
	pthread_mutex_destroy(&philosopher->fork);
	pthread_mutex_destroy(&philosopher->eating);
}

void	ft_mutexes_cleanup(t_monitor *monitor, t_philo *philosophers,
		pthread_mutex_t *global_mutexes)
{
	if (monitor->philosophers_nb == 1)
		ft_destroy_mutexes(philosophers);
	else
	{
		while (philosophers
			&& philosophers->id != philosophers->data.philosophers_nb)
			philosophers = philosophers->next;
		philosophers = philosophers->previous;
		while (philosophers && philosophers->id > 1)
		{
			ft_destroy_mutexes(philosophers->next);
			philosophers = philosophers->previous;
		}
		if (philosophers->id == 1)
		{
			ft_destroy_mutexes(philosophers->next);
			ft_destroy_mutexes(philosophers);
		}
	}
	pthread_mutex_destroy(&global_mutexes[0]);
	pthread_mutex_destroy(&global_mutexes[1]);
}

void	ft_memory_cleanup(t_philo *philosophers)
{
	if (philosophers->data.philosophers_nb == 1)
		free(philosophers);
	else
	{
		while (philosophers
			&& philosophers->id != philosophers->data.philosophers_nb)
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

void	ft_cleanup(t_monitor *monitor, t_philo *philosophers,
		pthread_mutex_t *global_mutexes)
{
	ft_thread_cleanup(monitor, philosophers);
	ft_mutexes_cleanup(monitor, philosophers, global_mutexes);
	ft_memory_cleanup(philosophers);
}
