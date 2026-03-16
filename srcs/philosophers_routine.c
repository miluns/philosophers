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
	if (*philosopher->everyone_alive)
	{
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
	pthread_mutex_lock(&philosopher->eating);
	philosopher->last_meal = ft_get_time_in_ms();
	pthread_mutex_unlock(&philosopher->eating);
	pthread_mutex_lock(&philosopher->fork);
	pthread_mutex_lock(philosopher->death);
	if (*philosopher->everyone_alive)
	{
		pthread_mutex_unlock(philosopher->death);
		ft_safe_print(philosopher, "has taken a fork");
		pthread_mutex_lock(philosopher->death);
		if (*philosopher->everyone_alive)
		{
			pthread_mutex_unlock(philosopher->death);
			pthread_mutex_lock(&philosopher->next->fork);
			ft_safe_print(philosopher, "has taken a fork");
		}
		else
		{
			pthread_mutex_unlock(philosopher->death);
			pthread_mutex_unlock(&philosopher->fork);
			return ;
		}
		pthread_mutex_lock(philosopher->death);
		if (*philosopher->everyone_alive)
		{
			pthread_mutex_unlock(philosopher->death);
			pthread_mutex_lock(&philosopher->eating);
			philosopher->last_meal = ft_get_time_in_ms();
			pthread_mutex_unlock(&philosopher->eating);
			ft_safe_print(philosopher, "is eating");
			ft_usleep(philosopher->data.time_to_eat);
			pthread_mutex_unlock(&philosopher->fork);
			pthread_mutex_unlock(&philosopher->next->fork);
			pthread_mutex_lock(&philosopher->eating);
			if (philosopher->data.times_to_eat > -1)
				philosopher->data.eating_turns++;
			pthread_mutex_unlock(&philosopher->eating);
		}
		else
		{
			pthread_mutex_unlock(philosopher->death);
			pthread_mutex_unlock(&philosopher->fork);
			pthread_mutex_unlock(&philosopher->next->fork);
		}
	}
	else
	{
		pthread_mutex_unlock(philosopher->death);
		pthread_mutex_unlock(&philosopher->fork);
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

void	*ft_single_philosopher_routine(void *arg)
{
	t_philo *philosopher;

	philosopher = (t_philo *)arg;
	pthread_mutex_lock(&philosopher->eating);
	philosopher->last_meal = ft_get_time_in_ms();
	pthread_mutex_unlock(&philosopher->eating);
	usleep(500);
	while (1)
	{
		pthread_mutex_lock(philosopher->death);
		if (!*philosopher->everyone_alive)
		{
			pthread_mutex_unlock(philosopher->death);
			break ;
		}
		ft_thinking(philosopher);
		ft_lonely_eating(philosopher);
	}
	return (NULL);
}

void	*ft_philosophers_routine(void *arg)
{
	t_philo *philosopher;

	philosopher = (t_philo *)arg;
	pthread_mutex_lock(&philosopher->eating);
	philosopher->last_meal = ft_get_time_in_ms();
	pthread_mutex_unlock(&philosopher->eating);
	if (philosopher->id % 2 != 0)
		usleep(500);
	while (1)
	{
		pthread_mutex_lock(philosopher->death);
		if (!*philosopher->everyone_alive)
		{
			pthread_mutex_unlock(philosopher->death);
			break ;
		}
		pthread_mutex_unlock(philosopher->death);
		ft_thinking(philosopher);
		ft_eating(philosopher);
		ft_sleeping(philosopher); 
	}
	return (NULL);
}
