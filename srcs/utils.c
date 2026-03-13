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

void	ft_initialize_global_mutexes(pthread_mutex_t *global_mutexes)
{
	pthread_mutex_init(&global_mutexes[0], NULL);
	pthread_mutex_init(&global_mutexes[1], NULL);
}

void	ft_print_philosophers_table(t_philo *philosophers)
{
	int	i;

	i = 0;
	while (i < philosophers->data.number_of_philosophers)
	{
		printf("ITERATION: %i\n%p	philo->id: %i\nphilo->next addr: %p\n",i, philosophers, philosophers->id, philosophers->next);
		i++;
		philosophers = philosophers->next;
	}
	printf("LIST PRINTED\n");
}