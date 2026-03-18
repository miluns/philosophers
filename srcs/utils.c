/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstawski <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:34:37 by mstawski          #+#    #+#             */
/*   Updated: 2026/03/18 13:55:30 by mstawski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

long	ft_get_time_in_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(long ms)
{
	long	start;

	if (ms <= 0)
		return ;
	start = ft_get_time_in_ms();
	while (ft_get_time_in_ms() - start < ms)
		usleep(500);
}

void	ft_safe_print(t_philo *philosopher, char *str)
{
	if (!philosopher || !str)
		return ;
	pthread_mutex_lock(philosopher->death);
	if (*philosopher->everyone_alive)
	{
		pthread_mutex_unlock(philosopher->death);
		pthread_mutex_lock(philosopher->print);
		printf("%ld %d %s\n", ft_get_time_in_ms(), philosopher->id, str);
		pthread_mutex_unlock(philosopher->print);
	}
	else
		pthread_mutex_unlock(philosopher->death);
}

void	ft_safe_print_monitor(t_philo *philosopher, char *str)
{
	if (!philosopher || !str)
		return ;
	pthread_mutex_lock(philosopher->print);
	printf("%ld %d %s\n", ft_get_time_in_ms(), philosopher->id, str);
	pthread_mutex_unlock(philosopher->print);
}
