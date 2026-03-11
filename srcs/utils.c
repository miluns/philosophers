#include "../philosophers.h"

int	ft_philo_atoi(const char *nptr)
{
	int	numb;
	int	sign;

	numb = 0;
	sign = 0;
	while ((*nptr > 6 && *nptr < 14) || *nptr == 32)
		nptr++;
	if (*nptr == 43 || *nptr == 45)
		sign += *(nptr++);
	while (*nptr > 47 && *nptr < 58)
		numb = numb * 10 + (*(nptr++) - 48);
	if (sign == 45)
		return (numb * (-1));
	return (numb);
}

