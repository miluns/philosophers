#include "../philosophers.h"

void	ft_thinking(t_philo *philosopher)
{
	pthread_mutex_lock(philosopher->death);
	if (philosopher->everyone_alive)
	{
		pthread_mutex_unlock(philosopher->death);
		ft_safe_print(philosopher, "is thinking");
	}
	else
		pthread_mutex_unlock(philosopher->death);
}

void	ft_eating(t_philo *philosopher)
{
	pthread_mutex_lock(&philosopher->eating);
	philosopher->last_meal = ft_get_time_in_ms();
	pthread_mutex_unlock(&philosopher->eating);
	pthread_mutex_lock(philosopher->death);
	if (philosopher->everyone_alive)
	{
		pthread_mutex_unlock(philosopher->death);
		pthread_mutex_lock(&philosopher->fork);
		ft_safe_print(philosopher, "has taken a fork");
		if (philosopher->data.number_of_philosophers > 1)
		{
			pthread_mutex_lock(philosopher->death);
			if (philosopher->everyone_alive)
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
		}
		pthread_mutex_lock(philosopher->death);
		if (philosopher->everyone_alive)
		{
			pthread_mutex_unlock(&philosopher->death);
			pthread_mutex_lock(&philosopher->eating);
			philosopher->last_meal = ft_get_time_in_ms();
			pthread_mutex_unlock(&philosopher->eating);
			ft_safe_print(philosopher, "is eating");
			ft_usleep(philosopher->data.time_to_eat);
			pthread_mutex_unlock(&philosopher->fork);
			if (philosopher->data.number_of_philosophers > 1)
				pthread_mutex_unlock(&philosopher->next->fork);
		}
		else
			pthread_mutex_unlock(philosopher->death);
	}
	else
			pthread_mutex_unlock(philosopher->death);
}

void	ft_sleeping(t_philo *philosopher)
{
	pthread_mutex_lock(philosopher->death);
	if (philosopher->everyone_alive)
	{
		pthread_mutex_unlock(philosopher->death);
		ft_safe_print(philosopher, "is sleeping");
		ft_usleep(philosopher->data.time_to_sleep);
	}
	else
		pthread_mutex_unlock(philosopher->death);
}

void	*ft_philosophers_routine(void *arg)
{
	t_philo *philosopher;

	philosopher = (t_philo *)arg;
	while (*philosopher->everyone_alive)
	{
		ft_thinking(philosopher);
		ft_eating(philosopher);
		ft_sleeping(philosopher); 
	}
	return (NULL);
}
