#ifndef PHILOSOPHERS_H
#define PHILOSPOHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct s_data
{
	int	nb_philo;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	pthread_mutex_t *forks;
	pthread_mutex_t print_lock;
}	t_data;

typedef struct s_philo
{
	int	id;
	pthread_t	thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data	*data;
}	t_philo;
