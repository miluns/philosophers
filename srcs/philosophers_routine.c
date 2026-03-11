#include "../philosophers.h"

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
	philosopher->data.eating_turns++;
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
