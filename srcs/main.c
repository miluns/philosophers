/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstawski <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 13:21:52 by mstawski          #+#    #+#             */
/*   Updated: 2026/03/05 20:10:20 by mstawski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	main(int argc, char *argv[])
{
	t_data	start_settings;
	t_monitor	monitor;
	t_philo	*philosophers;
	pthread_mutex_t global_mutexes[2];

	if (ft_input_validation(argc, argv))
	{
		philosophers = NULL;
		if (ft_parsing(&start_settings, argv))
		{
			if(ft_create_philosophers_table(&philosophers, start_settings, global_mutexes))
			{
				ft_create_monitoring_system(&monitor, philosophers);
				ft_create_monitoring_system_thread(&monitor);
				ft_create_philosophers_threads(philosophers, &monitor);
			}
			ft_cleanup(philosophers);
		}
	}
	return (1);
}
