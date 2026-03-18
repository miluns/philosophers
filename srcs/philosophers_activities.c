/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_activities.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstawski <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:33:24 by mstawski          #+#    #+#             */
/*   Updated: 2026/03/18 13:33:26 by mstawski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	ft_thinking(t_philo *philosopher)
{
	pthread_mutex_lock(philosopher->death);
	if (*philosopher->everyone_alive)
	{
		pthread_mutex_unlock(philosopher->death);
		ft_safe_print(philosopher, "is thinking");
	}
	else
		pthread_mutex_unlock(philosopher->death);
}

void	ft_lonely_eating(t_philo *philosopher)
{
	pthread_mutex_lock(philosopher->death);
	if (*philosopher->everyone_alive)
	{
		pthread_mutex_unlock(philosopher->death);
		pthread_mutex_lock(&philosopher->fork);
		ft_safe_print(philosopher, "has taken a fork");
		pthread_mutex_unlock(&philosopher->fork);
		ft_usleep(philosopher->data.time_to_die + 1);
	}
	else
		pthread_mutex_unlock(&philosopher->eating);
}

void	ft_eating(t_philo *philosopher)
{
	if (philosopher->id % 2 == 0)
	{
		ft_take_your_fork(philosopher);
		ft_take_neighbors_fork(philosopher);
		ft_eat_and_release_forks(philosopher);
	}
	else
	{
		ft_take_neighbors_fork(philosopher);
		ft_take_your_fork(philosopher);
		ft_eat_and_release_forks(philosopher);
	}
}

void	ft_sleeping(t_philo *philosopher)
{
	pthread_mutex_lock(philosopher->death);
	if (*philosopher->everyone_alive)
	{
		pthread_mutex_unlock(philosopher->death);
		ft_safe_print(philosopher, "is sleeping");
		ft_usleep(philosopher->data.time_to_sleep);
	}
	else
		pthread_mutex_unlock(philosopher->death);
}
