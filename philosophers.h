#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_data
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	times_to_eat;
	int	eating_turns;
}	t_data;

typedef struct s_philo
{
	int	id;
	int	*everyone_alive;
	long	last_meal;
	pthread_t	thread;
	pthread_mutex_t	fork;
	pthread_mutex_t	eating;
	pthread_mutex_t *death;
	pthread_mutex_t *print;
	t_data	data;
	struct s_philo	*previous;
	struct s_philo	*next;
}	t_philo;

typedef struct s_monitor
{
	pthread_t	thread;
	t_philo	*philosophers;
	int	everyone_alive;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	times_to_eat;
	int	number_of_philosophers;
	int	stuffed_philosophers;
}	t_monitor;

bool	ft_input_validation(int arg, char **input);
bool	ft_parsing(t_data *start_settings, char **arguments);

void	ft_initialize_global_mutexes(pthread_mutex_t *global_mutexes);

bool	ft_create_philosophers_table(t_philo **philosophers, t_data start_settings, pthread_mutex_t *global_mutexes);
t_philo	*ft_create_philosopher(t_data start_settings, int philosopher_id, pthread_mutex_t *global_mutexes);
void	ft_create_philosophers_threads(t_philo *philosophers, t_monitor *monitor);

void	ft_create_monitoring_system(t_monitor *monitor, t_philo *philosophers);
void	ft_create_monitoring_system_thread(t_monitor *monitor);

void	*ft_monitoring_system(void *arg);
void	*ft_monitoring_system_individual_plan(void *arg);

void    *ft_philosophers_routine(void *arg);
void    ft_eating(t_philo *philosopher);
void    ft_sleeping(t_philo *philosopher);

long	ft_get_time_in_ms(void);
void	ft_usleep(long ms);
void	ft_safe_print(t_philo *philosopher, char *str);

void	ft_cleanup(t_monitor *monitor, t_philo *philosophers, pthread_mutex_t *global_mutexes);

void	ft_print_philosophers_table(t_philo *philosophers);
int	ft_philo_atoi(const char *nptr);

#endif
