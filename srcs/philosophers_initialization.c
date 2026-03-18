/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_initialization.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstawski <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:33:54 by mstawski          #+#    #+#             */
/*   Updated: 2026/03/18 13:45:25 by mstawski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	*ft_single_philosopher_routine(void *arg)
{
	t_philo	*philosopher;

	philosopher = (t_philo *)arg;
	pthread_mutex_lock(&philosopher->eating);
	philosopher->last_meal = ft_get_time_in_ms();
	pthread_mutex_unlock(&philosopher->eating);
	ft_thinking(philosopher);
	ft_lonely_eating(philosopher);
	return (NULL);
}

void	*ft_philosophers_routine(void *arg)
{
	t_philo	*philosopher;

	philosopher = (t_philo *)arg;
	pthread_mutex_lock(&philosopher->eating);
	philosopher->last_meal = ft_get_time_in_ms();
	pthread_mutex_unlock(&philosopher->eating);
	while (1)
	{
		ft_thinking(philosopher);
		ft_eating(philosopher);
		ft_sleeping(philosopher);
		pthread_mutex_lock(philosopher->death);
		if (!*philosopher->everyone_alive)
		{
			pthread_mutex_unlock(philosopher->death);
			break ;
		}
		pthread_mutex_unlock(philosopher->death);
	}
	return (NULL);
}

void	ft_create_philosophers_threads(t_philo *philosophers,
		t_monitor *monitor)
{
	int	i;

	i = 0;
	if (philosophers->data.philosophers_nb == 1)
	{
		philosophers->everyone_alive = &monitor->everyone_alive;
		pthread_create(&philosophers->thread, NULL,
			ft_single_philosopher_routine, philosophers);
		return ;
	}
	while (i < philosophers->data.philosophers_nb)
	{
		philosophers->everyone_alive = &monitor->everyone_alive;
		philosophers->stuffed_philosophers = &monitor->stuffed_philosophers;
		pthread_create(&philosophers->thread, NULL,
			ft_philosophers_routine, philosophers);
		philosophers = philosophers->next;
		i++;
	}
}

t_philo	*ft_create_philosopher(t_data start_settings, int philosopher_id,
		pthread_mutex_t *global_mutexes)
{
	t_philo	*new_philosopher;

	new_philosopher = malloc(sizeof(t_philo));
	if (!new_philosopher)
		return (NULL);
	new_philosopher->id = philosopher_id;
	new_philosopher->stuffed = 0;
	new_philosopher->everyone_alive = NULL;
	new_philosopher->stuffed_philosophers = NULL;
	new_philosopher->last_meal = 0;
	new_philosopher->death = &global_mutexes[0];
	new_philosopher->print = &global_mutexes[1];
	new_philosopher->data.philosophers_nb = start_settings.philosophers_nb;
	new_philosopher->data.time_to_die = start_settings.time_to_die;
	new_philosopher->data.time_to_eat = start_settings.time_to_eat;
	new_philosopher->data.time_to_sleep = start_settings.time_to_sleep;
	new_philosopher->data.times_to_eat = start_settings.times_to_eat;
	new_philosopher->data.eating_turns = 0;
	new_philosopher->previous = NULL;
	new_philosopher->next = NULL;
	pthread_mutex_init(&new_philosopher->fork, NULL);
	pthread_mutex_init(&new_philosopher->eating, NULL);
	return (new_philosopher);
}

bool	ft_create_philosophers_table(t_philo **philosophers,
		t_data start_settings, pthread_mutex_t *global_mutexes)
{
	t_philo	*philosopher;
	int		i;

	philosopher = ft_create_philosopher(start_settings, 1, global_mutexes);
	*philosophers = philosopher;
	if (start_settings.philosophers_nb == 1)
		return (true);
	i = 1;
	while (i < start_settings.philosophers_nb)
	{
		philosopher->next = ft_create_philosopher(start_settings,
				i + 1, global_mutexes);
		if (philosopher->next == NULL)
			return (false);
		philosopher->next->previous = philosopher;
		philosopher = philosopher->next;
		i++;
	}
	philosopher->next = *philosophers;
	(*philosophers)->previous = philosopher;
	return (true);
}
