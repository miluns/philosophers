/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstawski <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 13:21:52 by mstawski          #+#    #+#             */
/*   Updated: 2026/03/05 20:10:20 by mstawski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_cleanup(t_philo *philosophers)
{
	while (philosophers && philosophers->id != philosophers->data.nb_philo)
		philosophers = philosophers->next;
	philosophers = philosophers->previous;
	while (philosophers && philosophers->id > 1)
	{
		pthread_join(&philosophers->next->thread, NULL);
		pthread_mutex_destroy(philosophers->next->fork);
		free(philosophers->next);
		philosophers = philosophers->previous;
	}
	if (philosophers->id == 1)
	{
		pthread_join(&philosophers->thread, NULL);
		pthread_mutex_destroy(philosophers->fork);
		free(philosophers);
	}
}

/*void	ft_dyi(t_node *philosophers)
{
	t_time_log	time;

	gettimeofday(&time.start, NULL);

	usleep(philosophers->philosopher->data->time_to_die * 1000);
	gettimeofday(&time.end, NULL);
	time.seconds = end.tv_sec - start.tv_sec;
	time.microseconds = end.tv_usec - start.tv_usec;
	time.elapsed = time.seconds + time.microseconds * 1e-6;
	philosophers->philosopher->data->time_to_die -= time.elapsed;
	if (philosophers->philosopher->data->time_to_die <= 0)
		philosophers->philosopher->data->is_alive = false;
	return ;
}*/

/*void	ft_sleeping(t_philo *philosophers)
{
	t_time_log	time;


	gettimeofday(&time.start, NULL);
	usleep(philosophers->philosopher->data->time_to_sleep * 1000);
	gettimeofday(&time.end, NULL);
	time.seconds = end.tv_sec - start.tv_sec;
	time.microseconds = end.tv_usec - start.tv_usec;
	time.elapsed = time.seconds + time.microseconds * 1e-6;
	philosophers->philosopher->data->time_to_die -= time.elapsed;
	if (philosophers->philosopher->data->time_to_die <= 0)
		philosophers->philosopher->data->is_alive = false;
	return ;
}

void	ft_eating(t_node *philosophers)
{
	gettimeofday(&time.start, NULL);
	usleep(philosophers->philosopher->data->time_to_eat * 1000); //
	gettimeofday(&time.end, NULL);
	time.seconds = end.tv_sec - start.tv_sec;
	time.microseconds = end.tv_usec - start.tv_usec;
	time.elapsed = time.seconds + time.microseconds * 1e-6; // do my own func
	philosophers->philosopher.data.time_to_die -= time.elapsed;
	return ;
}*/

void	ft_philosophers_routine(t_philo *philosophers)
{
	while (philosophers->is_alive)
	{
		ft_eating(philosophers);
		ft_sleeping(philosophers); 
	}
}

void	ft_monitoring_system(t_monitor monitor)
{
	while (1)
	{
		
	}
}

t_monitor	*ft_create_monitoring_system(t_monitor *monitor, t_philo *philosophers)
{
	monitor->philosophers = philosophers;
	pthread_create(&monitor->thread, NULL, ft_monitoring_system, monitor);
}

t_philo	*ft_create_philosopher(t_data start_settings, int philosopher_id)
{
	t_philo	*new_philosopher;
	pthread_mutex_t fork;

	new_philosopher = malloc(sizeof(t_philo));
	if (!new_philosopher)
		return (NULL);
	new_philosopher->id = philosopher_id;
	new_philosopher->data.nb_philo = start_settings.nb_philo;
	new_philosopher->data.time_to_die = start_settings.time_to_die;
	new_philosopher->data.time_to_eat = start_settings.time_to_eat;
	new_philosopher->data.time_to_sleep = start_settings.time_to_sleep;
	new_philosopher->is_alive = true;
	pthread_create(&new_philosopher->thread, NULL, ft_philosophers_routine, &new_philosopher);
	pthread_mutex_init(&fork, NULL);
	new_philosopher->fork = &fork;
	new_philosopher->next = NULL;
	new_philosopher->previous = NULL;
	return (new_philosopher);
}

bool	ft_create_table(t_philo **philosophers, t_data start_settings)
{
	t_philo	*philosopher;
	int	i;

	philosopher = ft_create_philosopher(start_settings, 1);
	*philosophers = philosopher;
	i = 1;
	while (i <= start_settings.nb_philo)
	{
		philosopher->next = create_philopher(start_settings, i + 1);
		if (philosopher->next == NULL)
			return (false);
		philosopher->next->previous = philosopher;
		philosopher = philosopher->next;
		i++;
	}
	(*philosophers)->previous = philosopher;
	return (true);
}

bool	ft_parsing(t_data *start_settings, char **arguments)
{
	start_settings->nb_philo = ft_atoi(arguments[1]);
    if (start_settings->nb_philo < 0)
        return false;
	start_settings->time_to_die = ft_atoi(arguments[2]);
    if (start_settings->time_to_die < 0)
        return false;
	start_settings->time_to_eat = ft_atoi(arguments[3]);
    if (start_settings->time_to_eat < 0)
        return false;
	start_settings->time_to_sleep = ft_atoi(arguments[4]);
    if (start_settings->time_to_sleep < 0)
        return false;
	return (true);
}

bool	ft_input_validation(char **input)
{
	while (*input)
	{
		while (**input)
		{
			if (**input < 48 && **input > 57)
				return (false);
			*input++;
		}
		input++;
	}
	return (true);
}

int	main(int argc, char *argv[])
{
	t_data	start_settings;
	t_philo *philosophers;
	t_monitor	monitor;

	ft_input_validation(argv);
	ft_parsing(&start_settings, argv);
	ft_create_table(&philosophers, start_settings);
	ft_create_monitoring_system(&monitor, philosophers);
}
