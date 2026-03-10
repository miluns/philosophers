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

long	get_time_in_ms(void)
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
	printf("%ld %d %s\n", ft_get_time_in_ms(), philosopher->id, str);
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

void	ft_sleeping(t_philo *philosopher)
{
	ft_safe_print(philosopher, "is sleeping");
	ft_usleep(philosopher->data.time_to_sleep);
}

void	ft_eating(t_philo *philosopher)
{
	ft_safe_print(philosopher, "is thinking");
	pthread_mutex_lock(philosopher->fork);
	if (philosopher->data.nb_philo > 1)
		pthread_mutex_lock(philosopher->next->fork);
	philosopher->last_meal = ft_get_time_in_ms();
	ft_safe_print(philosopher, "has taken a fork");
	ft_safe_print(philosopher, "is eating");
	philosopher->data.spaghetti_turns++;
	ft_usleep(philosopher->data.time_to_eat);
	philosopher->last_meal = ft_get_time_in_ms();
	pthread_mutex_unlock(philosopher->fork);
	if (philosopher->data.nb_philo > 1)
		pthread_mutex_unlock(philosopher->next->fork);
}

void	*ft_philosophers_routine(void *arg)
{
	t_philo *philosophers;

	philosophers = (t_philo *)arg;
	while (philosophers->is_alive)
	{
		ft_eating(philosophers);
		ft_sleeping(philosophers); 
	}
	return (NULL);
}

void	ft_individual_plan(t_monitor *monitor)
{
	while (1)
	{
		if (get_time_in_ms() - monitor->philosophers->last_meal > (long)monitor->time_to_die) 
		{
			ft_safe_print(monitor->philosophers, "died");
			monitor->philosophers->is_alive = false;
			monitor->everyone_alive = false;
			break ;
		}
	}
}

void	*ft_monitoring_system(void *arg)
{
	t_monitor	*monitor;

	monitor = (t_monitor *)arg;
	if (monitor->philosophers->data.nb_philo == 1)
	{
		ft_individual_plan(monitor);
		return (NULL);
	}
	while (1)
	{
		if (get_time_in_ms() - monitor->philosophers->last_meal > (long)monitor->time_to_die) 
		{
			ft_safe_print(monitor->philosophers, "died");
			monitor->philosophers->is_alive = false;
			monitor->everyone_alive = false;
			break ;
		}
		else
			monitor->philosophers = monitor->philosophers->next;
	}
	return (NULL);
}

void	ft_create_philosophers_threads(t_philo *philosophers)
{
	int	i;

	i = 0;
	while (i < philosophers->data.nb_philo)
	{
		pthread_create(&philosophers->thread, NULL, ft_philosophers_routine, &philosophers);
		philosophers = philosophers->next;
		i++;
	}
}

void	ft_create_monitoring_system(t_monitor *monitor, t_philo *philosophers)
{
	monitor->philosophers = philosophers;
	monitor->everyone_alive = true;
	monitor->time_to_die = philosophers->data.time_to_die;
	monitor->time_to_eat = philosophers->data.time_to_eat;
	monitor->time_to_sleep = philosophers->data.time_to_sleep;
	monitor->spaghetti_turns = philosophers->data.spaghetti_turns;
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
	new_philosopher->data.spaghetti_turns = start_settings.spaghetti_turns;
	new_philosopher->is_alive = true;
	new_philosopher->fork = &fork;
	new_philosopher->next = NULL;
	new_philosopher->previous = NULL;
	pthread_mutex_init(&fork, NULL);
	return (new_philosopher);
}

bool	ft_create_table(t_philo **philosophers, t_data start_settings)
{
	t_philo	*philosopher;
	int	i;

	philosopher = ft_create_philosopher(start_settings, 1);
	*philosophers = philosopher;
	if (start_settings.nb_philo == 1)
		return (true);
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
	if (start_settings.nb_philo > 1)
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
	start_settings->spaghetti_turns = ft_atoi(arguments[5]);
	if (start_settings->spaghetti_turns < 0)
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
	t_monitor	monitor;
	t_philo	*philosophers;

	ft_input_validation(argv);
	ft_parsing(&start_settings, argv);
	ft_create_table(&philosophers, start_settings);
	ft_create_monitoring_system(&monitor, philosophers);
	ft_create_philosophers_threads(philosophers);
}
