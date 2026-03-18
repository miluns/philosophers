/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstawski <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:33:35 by mstawski          #+#    #+#             */
/*   Updated: 2026/03/18 13:35:22 by mstawski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	ft_take_your_fork(t_philo *philosopher)
{
	pthread_mutex_lock(&philosopher->fork);
	pthread_mutex_lock(philosopher->death);
	if (*philosopher->everyone_alive)
	{
		pthread_mutex_unlock(philosopher->death);
		ft_safe_print(philosopher, "has taken a fork");
	}
	else
		pthread_mutex_unlock(philosopher->death);
}

void	ft_take_neighbors_fork(t_philo *philosophers)
{
	pthread_mutex_lock(&philosophers->previous->fork);
	pthread_mutex_lock(philosophers->death);
	if (*philosophers->everyone_alive)
	{
		pthread_mutex_unlock(philosophers->death);
		ft_safe_print(philosophers, "has taken a fork");
	}
	else
		pthread_mutex_unlock(philosophers->death);
}

void	ft_eat_and_release_forks(t_philo *philosophers)
{
	pthread_mutex_lock(philosophers->death);
	if (*philosophers->everyone_alive)
	{
		pthread_mutex_unlock(philosophers->death);
		pthread_mutex_lock(&philosophers->eating);
		philosophers->last_meal = ft_get_time_in_ms();
		if (philosophers->data.times_to_eat > -1)
			philosophers->data.eating_turns++;
		pthread_mutex_unlock(&philosophers->eating);
		ft_safe_print(philosophers, "is eating");
		ft_usleep(philosophers->data.time_to_eat);
		ft_release_forks(philosophers);
	}
	else
	{
		pthread_mutex_unlock(philosophers->death);
		ft_release_forks(philosophers);
	}
}

void	ft_release_forks(t_philo *philosophers)
{
	if (philosophers->id % 2 == 0)
	{
		pthread_mutex_unlock(&philosophers->fork);
		pthread_mutex_unlock(&philosophers->previous->fork);
	}
	else
	{
		pthread_mutex_unlock(&philosophers->previous->fork);
		pthread_mutex_unlock(&philosophers->fork);
	}
}
