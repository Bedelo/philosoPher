#include "../includes/philosopher.h"


static void	*m_routine(void *arg)
{
	t_data *data = (t_data *)arg;
	int		off;

	off = 0;
	while (!off)
	{
		printf("OOOOOOOOOOOOOOOOOOOOOOO\n");
		if(data->death == 1 || data->meals_max > 0)
		{
			clear_if_dead(data);
			off = 1;
			printf("UUUUUUUUUUUUUUUUUUUUUU\n");
		}
			
		
		usleep(10);
	}
	return (arg);
}

void	monitoring_creation(t_data *data)
{
	pthread_create(&(data->monitoring_t), NULL, m_routine, (void *)(data));
}


void	monitoring_join(t_data *data)
{
	pthread_join(data->monitoring_t, NULL);
}
