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
	size_t	number_of_philosophers;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	times_to_eat;
	size_t	eating_turns;
}	t_data;

typedef struct s_philo
{
	int	id;
	bool	is_alive;
	long	last_meal;
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
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	times_to_eat;
	size_t	number_of_philosophers;
	size_t	stuffed_philosophers;
}	t_monitor;

bool	ft_input_validation(char **input);
bool	ft_parsing(t_data *start_settings, char **arguments);

bool	ft_create_philosophers_table(t_philo **philosophers, t_data start_settings);
t_philo	*ft_create_philosopher(t_data start_settings, int philosopher_id);
void	ft_create_philosophers_threads(t_philo *philosophers);

void	ft_create_monitoring_system(t_monitor *monitor, t_philo *philosophers);
void	ft_create_monitoring_system_thread(t_monitor *monitor);

void	*ft_monitoring_system(void *arg);
void	ft_monitoring_system_individual_plan(t_monitor *monitor);

void    *ft_philosophers_routine(void *arg);
void    ft_eating(t_philo *philosopher);
void    ft_sleeping(t_philo *philosopher);

long	get_time_in_ms(void);
void	ft_usleep(long ms);
void	ft_safe_print(t_philo *philosopher, char *str);

void	ft_cleanup(t_philo *philosophers);

int	ft_philo_atoi(const char *nptr);

#endif
