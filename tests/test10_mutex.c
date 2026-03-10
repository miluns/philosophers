#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef	struct s_sranie
{
	int	id;
	pthread_t	thread;
	pthread_mutex_t	sikanie;
	pthread_mutex_t	sranie;
}	t_sranie;

typedef	struct s_myslenie
{
	pthread_t	thread;
	t_sranie	*sranie;
}	t_myslenie;

void	*klozet(void *myslenie_na_sraczu)
{
	t_myslenie *kurwo = (t_myslenie *)myslenie_na_sraczu;

	while (1)
	{
		pthread_mutex_lock(&kurwo->sranie->sranie);
		printf("Mysliciel sranie - chwila przerwy w mysleniu\n");
		usleep(500000);
		pthread_mutex_unlock(&kurwo->sranie->sranie);
		printf("Mysliciel przerwa w sraniu\n");
		usleep(1000000);
	}
	return (NULL);
}

void	*walenie_kloca(void *sranie)
{
	t_sranie	*kurwo = (t_sranie *)sranie;
	while (1)
	{
		pthread_mutex_lock(&kurwo->sikanie);
		printf("Watek %i: sika\n", kurwo->id);	
		usleep(500000);
		pthread_mutex_unlock(&kurwo->sikanie);
		printf("Watek %i: przygotowuje sie do srania\n", kurwo->id);
		usleep(1000000);
		pthread_mutex_lock(&kurwo->sranie);
		printf("Watek %i: sra\n", kurwo->id);	
		usleep(500000);
		pthread_mutex_unlock(&kurwo->sranie);
	}
	return (NULL);
}

int	main(void)
{
	t_myslenie	myslenie_na_sraczu;
	t_sranie	*sranie;
	
	sranie = malloc(sizeof(t_sranie) * 2);
	sranie[0].id = 1;
	sranie[1].id = 2;
	myslenie_na_sraczu.sranie = sranie;
	pthread_mutex_init(&sranie[0].sikanie, NULL);
	pthread_mutex_init(&sranie[0].sranie, NULL);
	pthread_mutex_init(&sranie[1].sikanie, NULL);
	pthread_mutex_init(&sranie[1].sranie, NULL);

	pthread_create(&sranie[0].thread, NULL, walenie_kloca, &sranie[0]);
	pthread_create(&sranie[1].thread, NULL, walenie_kloca, &sranie[1]);
	pthread_create(&myslenie_na_sraczu.thread, NULL, klozet, &myslenie_na_sraczu);

	pthread_join(sranie[0].thread, NULL);
	pthread_join(sranie[1].thread, NULL);
	pthread_join(myslenie_na_sraczu.thread, NULL);
}
