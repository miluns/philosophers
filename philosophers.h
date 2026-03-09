#ifndef PHILOSOPHERS_H
#define PHILOSPOHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_time_log
{
	struct timeval start;
	struct timeval end;
	long seconds;
	long microseconds;
	double elapsed;
}	t_time_log;	

typedef struct s_error
{
	int	input_validation;
	int	parsing;
	int	create_table;
}	t_error;

typedef struct s_data
{
	int	nb_philo;
	bool	is_alive;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	pthread_mutex_t	*last_meal;
}	t_data;

typedef struct s_philo
{
	int	id;
	pthread_t	thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data	*data;
}	t_philo;

typedef struct s_node
{
	t_philo	*philosopher;
	struct s_node	*previous;
	struct s_node	*next;
}	t_node;

#endif
