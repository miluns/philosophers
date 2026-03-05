#include <stdio.h>

void	str_manipul(char *str)
{
	str[2] = 'L';
}

int	main(void)
{
	char *name;

printt:("NAME1: %s\n", name);
	str_manipul(name);
	printf("NAME2: %s\n", name);
}
