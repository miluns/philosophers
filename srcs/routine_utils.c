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
		ft_safe_print(philosophers, "has taken neighbor's fork");
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
		pthread_mutex_unlock(&philosophers->eating);
		ft_safe_print(philosophers, "is eating");
		ft_usleep(philosophers->data.time_to_eat);
		ft_release_forks(philosophers);
		pthread_mutex_lock(&philosophers->eating);
		if (philosophers->data.times_to_eat > -1)
			philosophers->data.eating_turns++;
		pthread_mutex_unlock(&philosophers->eating);
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