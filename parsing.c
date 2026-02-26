int    ft_parser(t_data *data, char **arguments)
{
    data->nb_philo = atoi(arguments[1]);
    if (data->nb_philo < 0)
        return 1;
    data->time_to_die = atoi(arguments[2]);
    if (data->time_to_die < 0)
        return 2;
    data->time_to_eat = atoi(arguments[3]);
    if (data->time_to_eat < 0)
        return 3;
    data->time_to_sleep = atoi(arguments[4]);
    if (data->time_to_sleep < 0)
        return 4;

}