#include "../includes/philosopher.h"


static void	*m_routine(void *arg)
{
	t_data	*data ;
	int		off;

	data = (t_data *)arg;
	off = 0;
	while (!off)
	{
		if (data->death > 0
			|| data->meals_over == data->nb_philos)
		{
			clear_if_dead(data);
			off = 1;
		}
		usleep(1);
	}
	printf("FIN\n");
	return (NULL);
}

void	monitoring_creation(t_data *data)
{
	pthread_create(&(data->monitoring_t), NULL, m_routine, (void *)(data));
}


int	monitoring_join(t_data *data)
{
	return pthread_join(data->monitoring_t, NULL);
}

void	clear_if_dead(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		data->philos[i].run = 0;
		i++;
	}
	pthread_mutex_destroy(&data->printable);
}
