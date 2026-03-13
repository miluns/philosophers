#include "../philosophers.h"

void	ft_create_philosophers_threads(t_philo *philosophers, t_monitor *monitor)
{
	int	i;

	i = 0;
	printf("furious at this point\n");
	while (i < philosophers->data.number_of_philosophers)
	{
		philosophers->everyone_alive = &monitor->everyone_alive;
		pthread_create(&philosophers->thread, NULL, ft_philosophers_routine, philosophers);
		philosophers = philosophers->next;
		i++;
	}
}

t_philo	*ft_create_philosopher(t_data start_settings, int philosopher_id, pthread_mutex_t *global_mutexes)
{
	t_philo	*new_philosopher;

	new_philosopher = malloc(sizeof(t_philo));
	if (!new_philosopher)
		return (NULL);
	new_philosopher->id = philosopher_id;
	new_philosopher->everyone_alive = NULL;
	new_philosopher->last_meal = 0;
	new_philosopher->death = &global_mutexes[0];
	new_philosopher->print = &global_mutexes[1];
	new_philosopher->data.number_of_philosophers = start_settings.number_of_philosophers;
	new_philosopher->data.time_to_die = start_settings.time_to_die;
	new_philosopher->data.time_to_eat = start_settings.time_to_eat;
	new_philosopher->data.time_to_sleep = start_settings.time_to_sleep;
	new_philosopher->data.times_to_eat = start_settings.times_to_eat;
	new_philosopher->data.eating_turns = 0;
	new_philosopher->previous = NULL;
	new_philosopher->next = NULL;
	pthread_mutex_init(&new_philosopher->fork, NULL);
	pthread_mutex_init(&new_philosopher->eating, NULL);
	return (new_philosopher);
}

bool	ft_create_philosophers_table(t_philo **philosophers, t_data start_settings, pthread_mutex_t *global_mutexes)
{
	t_philo	*philosopher;
	int	i;

	philosopher = ft_create_philosopher(start_settings, 1, global_mutexes);
	*philosophers = philosopher;
	if (start_settings.number_of_philosophers == 1)
		return (true);
	i = 1;
	while (i < start_settings.number_of_philosophers)
	{
		philosopher->next = ft_create_philosopher(start_settings, i + 1, global_mutexes);
		if (philosopher->next == NULL)
			return (false);
		philosopher->next->previous = philosopher;
		philosopher = philosopher->next;
		i++;
	}
	(*philosophers)->previous = philosopher;
	return (true);
}
