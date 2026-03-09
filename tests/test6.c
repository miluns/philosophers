#include <stdio.h>

void	pass_two(int n)
{
	printf("PASS TWO N: %i\n", n);
}

void	pass_one(int n)
{
	printf("PASS ONE N: %i\n", n);
	pass_two(n);
}

int	main(void)
{
	printf("n = %i\n", 5);
	pass_one(5);
}
