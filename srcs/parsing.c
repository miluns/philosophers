#include "../philosophers.h"

bool	ft_parsing(t_data *start_settings, char **arguments)
{
	start_settings->number_of_philosophers = ft_philo_atoi(arguments[1]);
	if (start_settings->number_of_philosophers <= 0)
		return (false);
	start_settings->time_to_die = ft_philo_atoi(arguments[2]);
	if (start_settings->time_to_die < 0)
		return (false);
	start_settings->time_to_eat = ft_philo_atoi(arguments[3]);
	if (start_settings->time_to_eat < 0)
        return (false);
	start_settings->time_to_sleep = ft_philo_atoi(arguments[4]);
	if (start_settings->time_to_sleep < 0)
		return (false);
	start_settings->times_to_eat = ft_philo_atoi(arguments[5]);
	if (start_settings->times_to_eat < 0)
        return (false);
	return (true);
}

bool	ft_input_validation(int argc, char **input)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
		return (false);
	i = 0;
	j = 0;
	while (input[i])
	{
		while (input[i][j])
		{
			if (input[i][j] < 48 && input[i][j] > 57)
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}
