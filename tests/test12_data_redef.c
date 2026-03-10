#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct	s_data
{
	int number;
}	t_data;
	
typedef struct	s_struktura_in
{
	pthread_t thread;
	t_data	data;	
}	t_struktura_in;

typedef struct s_struktura_out
{
	t_struktura_in	*struktura_in;
	pthread_t thread;
}	t_struktura_out;

void	set_data(t_data *data)
{
	data->number = 5;
}

void	aloc_struktura_in(t_struktura_in **struktura_in)
{
	(*struktura_in) = malloc(sizeof(struktura_in));
	if (!*struktura_in)
		return ;
}

void	*cos_tam(void *arg)
{
	t_struktura_in	*struktura_in;
	struktura_in = (t_struktura_in *)arg;	
	printf("struktura_in->data.number = %i\n", struktura_in->data.number);
	printf("Czekanie na zmiane...\n");
	usleep(5000000);
	struktura_in->data.number = 10;
}

void	init_struktura_in(t_struktura_in *struktura_in, t_data datas)
{
	struktura_in->data.number = datas.number;
	pthread_create(&struktura_in->thread, NULL, cos_tam, struktura_in);
}

void	*cos_tego(void *arg)
{
	t_struktura_out	*struktura_out;

	struktura_out = (t_struktura_out *)arg;
	while (1)
	{
		printf("struktura_out->data.number: %i\n", struktura_out->struktura_in->data.number);
	}
}

void	init_struktura_out(t_struktura_out *struktura_out)
{
	pthread_create(&struktura_out->thread, NULL, cos_tego, struktura_out);
}

int	main(void)
{

	t_struktura_out	struktura_out;
	t_struktura_in	*struktura_in;
	t_data	data;
	
	set_data(&data);
	aloc_struktura_in(&struktura_in);	
	printf("data.number = %i\n", data.number);
	init_struktura_in(struktura_in, data);
	struktura_out.struktura_in = struktura_in;
	init_struktura_out(&struktura_out);

	pthread_join(struktura_in->thread, NULL);
	pthread_join(struktura_out.thread, NULL);
}
