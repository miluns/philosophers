/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstawski <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 13:21:52 by mstawski          #+#    #+#             */
/*   Updated: 2025/09/17 15:34:22 by mstawski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philophers.h"

/*t_node	ft_create_philosopher(t_data *start_settings, int philosopher_id) //To chyba jest bezsensu
{
	t_node	*new_philosopher;
	
	new_philospher = malloc(sizeof(t_node));
	if (!new_philosopher)
		return (NULL);
	new_philosopher->id = philosopher_id;
	new_philosopher->data->nb_philo = start_settings->nb_philo;
	new_philosopher->data->time_to_die = start_settings->time_to_die;
	new_philosopher->data->time_to_eat = start_settings->time_to_eat;
	new_philosopher->data->time_to_sleep = start_settings->time_to_sleep; LINKED LIST
	new_philosopher->next = NULL;
	new_philosopher->previous = NULL;
}*/

/*void	ft_create_table(t_node *table, t_data *start_settings)
{
	t_node	*head;
	int	i;

	table =
	(*table)->head = &philosopher;
	while (i < chairs)
	{
		philosopher->next = create_philopher(++i); LINKED LIST
		philosopher->previous = philosopher;
		philosopher = philosopher->next;
	}
	philosopher->next = (*table)->head;
	(*table)->head = philosopher;
}*/

int	ft_create_table(t_data *start_settings, t_philo *table, t_error *error)
{
	*table = malloc(sizeof(t_philo) * start_settings->nb_philo);
	if (*!table)
		return error->table_creation = 1;
	table[start_settings->nb_philo] = 0;
	return (error->table_creation = 0);
}

int    ft_parsing(t_data *start_settings, char *arguments, t_error &error)
{
	start_settings->nb_philo = ft_atoi(arguments[1]);
    if (start_settings->nb_philo <= 0)
        return error->parsing = 1;
	start_settings->time_to_die = ft_atoi(arguments[2]);
    if (start_settings->time_to_die <= 0)
        return error->parsing = 2;
	start_settings->time_to_eat = ft_atoi(arguments[3]);
    if (start_settings->time_to_eat <= 0)
        return error->parsing = 3;
	start_settings->time_to_sleep = ft_atoi(arguments[4]);
    if (start_settings->time_to_sleep <= 0)
        return error->parsing = 4;
	return (error->parsing = 0);
}

void	*ft_routine(void *philosopher)
{
	while (true)
	{
		think();
		eat();
		sleep();
	}
}

int	ft_threads_init(t_data *start_settings, t_philo *table, t_error *error)
{
	int	i;

	i = 0;
	while (i < start_settings->nb_philo)
	{
		pthread_create(&table[i]->thread, NULL, ft_routine, &table[i])
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_data	*start_settings;
	t_philo *table;
	t_error	*error;

	ft_parsing(&start_settings, argv, error);
	ft_create_table(&table, &start_settings, error);
	ft_threads_init(start_setting, table, error);
}
