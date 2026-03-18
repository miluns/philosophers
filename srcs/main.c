/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstawski <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 13:21:52 by mstawski          #+#    #+#             */
/*   Updated: 2026/03/18 13:55:07 by mstawski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	ft_initialize_global_mutexes(pthread_mutex_t *global_mutexes)
{
	pthread_mutex_init(&global_mutexes[0], NULL);
	pthread_mutex_init(&global_mutexes[1], NULL);
}

int	main(int argc, char *argv[])
{
	t_data			start_settings;
	t_monitor		monitor;
	t_philo			*philosophers;
	pthread_mutex_t	global_mutexes[2];

	if (ft_input_validation(argc, argv))
	{
		philosophers = NULL;
		if (ft_parsing(&start_settings, argv))
		{
			ft_initialize_global_mutexes(global_mutexes);
			if (ft_create_philosophers_table(&philosophers, start_settings,
					global_mutexes))
			{
				ft_create_monitoring_system(&monitor, philosophers);
				ft_create_monitoring_system_thread(&monitor);
				ft_create_philosophers_threads(philosophers, &monitor);
			}
			ft_cleanup(&monitor, philosophers, global_mutexes);
			return (0);
		}
	}
	return (1);
}
