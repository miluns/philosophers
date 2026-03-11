#include "../philosophers.h"

long	get_time_in_ms(void)
{
	struct timeval	time;
	
	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(long ms)
{
	long	start;

	if (ms <= 0)
		return ;
	start = ft_get_time_in_ms();
	while (ft_get_time_in_ms() - start < ms)
		usleep(500);
}

void	ft_safe_print(t_philo *philosopher, char *str)
{
	if (!philosopher || !str)
		return ;
	printf("%ld %d %s\n", ft_get_time_in_ms(), philosopher->id, str);
}
