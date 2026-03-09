#ifndef PHILOSOPHERS_H
#define PHILOSPOHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_data
{
	int	nb_philo;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
}	t_data;

typedef struct s_philo
{
	int	id;
	bool	is_alive;
	pthread_t	thread;
	pthread_mutex_t	*fork;
	t_data	data;
	struct s_philo	*previous;
	struct s_philo	*next;
}	t_philo;

typedef struct s_monitor
{
	pthread_t	thread;
	t_philo	*philosophers;
}	t_monitor;

#endif
