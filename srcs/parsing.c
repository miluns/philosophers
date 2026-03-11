#include "../philosophers.h"

bool	ft_parsing(t_data *start_settings, char **arguments)
{
	start_settings->nb_philo = ft_atoi(arguments[1]);
    if (start_settings->nb_philo < 0)
        return false;
	start_settings->time_to_die = ft_atoi(arguments[2]);
    if (start_settings->time_to_die < 0)
        return false;
	start_settings->time_to_eat = ft_atoi(arguments[3]);
    if (start_settings->time_to_eat < 0)
        return false;
	start_settings->time_to_sleep = ft_atoi(arguments[4]);
    if (start_settings->time_to_sleep < 0)
        return false;
	start_settings->spaghetti_turns = ft_atoi(arguments[5]);
	if (start_settings->spaghetti_turns < 0)
        return false;
	return (true);
}

bool	ft_input_validation(char **input)
{
	while (*input)
	{
		while (**input)
		{
			if (**input < 48 && **input > 57)
				return (false);
			*input++;
		}
		input++;
	}
	return (true);
