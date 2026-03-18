/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstawski <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 13:34:31 by mstawski          #+#    #+#             */
/*   Updated: 2026/03/18 13:37:48 by mstawski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	ft_philo_atoi(const char *nptr)
{
	int	numb;
	int	sign;

	if (!nptr || !*nptr)
		return (0);
	numb = 0;
	sign = 0;
	while ((*nptr > 6 && *nptr < 14) || *nptr == 32)
		nptr++;
	if (*nptr == 43 || *nptr == 45)
		sign += *(nptr++);
	while (*nptr > 47 && *nptr < 58)
	{
		numb *= 10;
		numb += (*(nptr++) - 48);
	}
	if (sign == 45)
		return (numb * (-1));
	return (numb);
}

bool	ft_parsing(t_data *start_settings, char **arguments)
{
	start_settings->philosophers_nb = ft_philo_atoi(arguments[1]);
	if (start_settings->philosophers_nb <= 0)
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
	if (arguments[5])
	{
		start_settings->times_to_eat = ft_philo_atoi(arguments[5]);
		if (start_settings->times_to_eat <= 0)
			return (false);
	}
	else
		start_settings->times_to_eat = -1;
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
