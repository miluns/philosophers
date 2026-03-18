/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstawski <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 14:12:42 by mstawski          #+#    #+#             */
/*   Updated: 2026/03/18 14:31:25 by mstawski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_data
{
	int	philosophers_nb;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	times_to_eat;
	int	eating_turns;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				stuffed;
	int				*everyone_alive;
	int				*stuffed_philosophers;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	fork;
	pthread_mutex_t	eating;
	pthread_mutex_t	*death;
	pthread_mutex_t	*print;
	t_data			data;
	struct s_philo	*previous;
	struct s_philo	*next;
}	t_philo;

typedef struct s_monitor
{
	pthread_t		thread;
	t_philo			*philosophers;
	int				everyone_alive;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_to_eat;
	int				philosophers_nb;
	int				stuffed_philosophers;
}	t_monitor;

//-----------------------------------------------------------------------------
//	PARSING (3)
//-----------------------------------------------------------------------------
bool	ft_input_validation(int arg, char **input);
bool	ft_parsing(t_data *start_settings, char **arguments);
int		ft_philo_atoi(const char *nptr);

//-----------------------------------------------------------------------------
//	PHILOSOPHERS_INITIALIZATION (5)
//-----------------------------------------------------------------------------
bool	ft_create_philosophers_table(t_philo **philosophers,
			t_data start_settings, pthread_mutex_t *global_mutexes);
t_philo	*ft_create_philosopher(t_data start_settings, int philosopher_id,
			pthread_mutex_t *global_mutexes);
void	ft_create_philosophers_threads(t_philo *philosophers,
			t_monitor *monitor);
void	*ft_philosophers_routine(void *arg);
void	*ft_single_philosopher_routine(void *arg);

//-----------------------------------------------------------------------------
//	PHILOSOPHERS_ACTIVITIES (4)
//-----------------------------------------------------------------------------
void	ft_thinking(t_philo *philosophers);
void	ft_eating(t_philo *philosopher);
void	ft_lonely_eating(t_philo *philosopher);
void	ft_sleeping(t_philo *philosopher);

//-----------------------------------------------------------------------------
//	FORKS_HANDLING (4)
//-----------------------------------------------------------------------------
void	ft_take_your_fork(t_philo *philosopher);
void	ft_take_neighbors_fork(t_philo *philosophers);
void	ft_eat_and_release_forks(t_philo *philosophers);
void	ft_release_forks(t_philo *philosophers);

//-----------------------------------------------------------------------------
//	MONITORING_SYSTEM_CREATION (2)
//-----------------------------------------------------------------------------
void	ft_create_monitoring_system(t_monitor *monitor, t_philo *philosophers);
void	ft_create_monitoring_system_thread(t_monitor *monitor);

//-----------------------------------------------------------------------------
//	MONITORING_SYSTEM (5)
//-----------------------------------------------------------------------------
void	*ft_monitoring_system(void *arg);
void	*ft_monitoring_system_individual_plan(void *arg);
bool	ft_philosophers_death_check(t_monitor *monitor);
bool	ft_philosophers_meals_check(t_monitor *monitor);
void	ft_update_death_flag(t_monitor *monitor, t_philo *philosopher);

//-----------------------------------------------------------------------------
//	CLEANUP	(5)
//-----------------------------------------------------------------------------
void	ft_cleanup(t_monitor *monitor, t_philo *philosophers,
			pthread_mutex_t *global_mutexes);
void	ft_thread_cleanup(t_monitor *monitor, t_philo *philosophers);
void	ft_mutexes_cleanup(t_monitor *monitor, t_philo *philosophers,
			pthread_mutex_t *global_mutexes);
void	ft_memory_cleanup(t_philo *philosophers);
void	ft_destroy_mutexes(t_philo *philosopher);

//-----------------------------------------------------------------------------
//	UTILS (4)
//-----------------------------------------------------------------------------
long	ft_get_time_in_ms(void);
void	ft_usleep(long ms);
void	ft_safe_print(t_philo *philosopher, char *str);
void	ft_safe_print_monitor(t_philo *philosopher, char *str);

#endif
