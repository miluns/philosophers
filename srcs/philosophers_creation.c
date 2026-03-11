#include "../philosophers.h"

void	ft_create_philosophers_threads(t_philo *philosophers)
{
	int	i;

	i = 0;
	while (i < philosophers->data.number_of_philosophers)
	{
		pthread_create(&philosophers->thread, NULL, ft_philosophers_routine, &philosophers);
		philosophers = philosophers->next;
		i++;
	}
}

t_philo	*ft_create_philosopher(t_data start_settings, int philosopher_id)
{
	t_philo	*new_philosopher;
	pthread_mutex_t fork;

	new_philosopher = malloc(sizeof(t_philo));
	if (!new_philosopher)
		return (NULL);
	new_philosopher->id = philosopher_id;
	new_philosopher->data.number_of_philosophers = start_settings.number_of_philosophers;
	new_philosopher->data.time_to_die = start_settings.time_to_die;
	new_philosopher->data.time_to_eat = start_settings.time_to_eat;
	new_philosopher->data.time_to_sleep = start_settings.time_to_sleep;
	new_philosopher->data.times_to_eat = start_settings.times_to_eat;
	new_philosopher->data.eating_turns = 0;
	new_philosopher->is_alive = true;
	new_philosopher->fork = &fork;
	new_philosopher->next = NULL;
	new_philosopher->previous = NULL;
	pthread_mutex_init(&fork, NULL);
	return (new_philosopher);
}

bool	ft_create_philosophers_table(t_philo **philosophers, t_data start_settings)
{
	t_philo	*philosopher;
	int	i;

	philosopher = ft_create_philosopher(start_settings, 1);
	*philosophers = philosopher;
	if (start_settings.number_of_philosophers == 1)
		return (true);
	i = 1;
	while (i <= start_settings.number_of_philosophers)
	{
		philosopher->next = create_philopher(start_settings, i + 1);
		if (philosopher->next == NULL)
			return (false);
		philosopher->next->previous = philosopher;
		philosopher = philosopher->next;
		i++;
	}
	(*philosophers)->previous = philosopher;
	return (true);
}
