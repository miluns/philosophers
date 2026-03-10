#include <stdio.h>

typedef struct s_sranie
{
	int	sikanie;
	int	sranie;
}	t_sranie;	

void	sranie_init(t_sranie *sranko)
{
	sranko->sikanie = 1;
	sranko->sranie = 1;	
}

int	main(void)
{
	t_sranie	sranko;
	
	sranie_init(&sranko);	
	printf("sranko.sikanie = %i\nsranko.sranie = %i\n", sranko.sikanie, sranko.sranie);
}
