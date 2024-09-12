#include "../includes/philosopher.h"


static void	*m_routine(void *arg)
{
	t_data *data = (t_data *)arg;
	int		off;
	int		i;

	off = 0;
	while (!off)
	{
		i = 0;
		while (i < data->nb_philos)
		{
			if(data->philos[i].run == 0)
			{
				clear_if_dead(data);
				off = 1;
			}
			i++;
		}
		usleep(100);
	}
	return (NULL);
}

void	monitoring_creation(t_data *data)
{
	pthread_create(&(data->monitoring_t), NULL, m_routine, (void *)(data));
}


void	monitoring_join(t_data *data)
{
	pthread_join(data->monitoring_t, NULL);
}
