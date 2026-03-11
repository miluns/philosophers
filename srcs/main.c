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

	if (ft_input_validation(argv))
		if (ft_parsing(&start_settings, argv))
			if(ft_create_philosophers_table(&philosophers, start_settings))
			{
				ft_create_monitoring_system(&monitor, philosophers);
				ft_create_monitoring_system_thread(&monitor);
				ft_create_philosophers_threads(philosophers);
			}
			ft_cleanup(philosophers);

	return (1);
}
