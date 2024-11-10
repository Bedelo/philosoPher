#include "../includes/philosopher.h"

static void	*m_routine(void *arg)
{
	t_data	*data ;
	int		id_dead;

	data = (t_data *)arg;
	while (1)
	{
		usleep(500);
		id_dead = get_i(&data->dead_mut, &data->first_dead);
		if (id_dead >= 0)
		{
			pthread_mutex_lock(&data->printable);
			{
				printf("%-7lld %-7d died\n",
					ft_time() - get_ll(&data->r_w, &data->time_of_begin),
					data->philos[id_dead].name + 1);
			}
			pthread_mutex_unlock(&(data->printable));
			break ;
		}
		if (data->nb_philos == get_i(&data->r_w, &data->meals_over))
			break ;
	}
	ft_sleep(100);
	return (NULL);
}

void	monitoring_creation(t_data *data)
{
	pthread_create(&(data->monitoring_t), NULL, m_routine, (void *)(data));
}

int	monitoring_join(t_data *data)
{
	return (pthread_join(data->monitoring_t, NULL));
}

// void	clear_if_dead(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	if (!pthread_mutex_lock(&data->r_w))
// 	{
// 		while (i < data->nb_philos)
// 		{
// 			if (!pthread_mutex_lock(&data->over))
// 			{
// 				data->philos[i].run = 0;
// 				pthread_mutex_unlock(&data->over);
// 			}
// 			i++;
// 		}
// 		pthread_mutex_unlock(&data->r_w);
// 	}
// }
