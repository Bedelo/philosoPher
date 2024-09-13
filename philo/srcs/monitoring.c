#include "../includes/philosopher.h"


static void	*m_routine(void *arg)
{
	t_data	*data ;
	int		off;

	data = (t_data *)arg;
	off = 0;
	while (!off)
	{
		// printf("LOL");
		if (data->death > 0 || data->meals_over > 0)
		{
			clear_if_dead(data);
			off = 1;
		}
		usleep(5);
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

void	clear_if_dead(t_data *data)
{
	int	i;

	i = 0;
	while(i < data->nb_philos)
		pthread_detach(data->philos[i].phi);
	pthread_mutex_destroy(&data->printable);
	pthread_mutex_destroy(&data->is_dead);
	free(data->philos);
}
