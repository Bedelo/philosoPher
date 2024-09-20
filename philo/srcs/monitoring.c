#include "../includes/philosopher.h"


static void	*m_routine(void *arg)
{
	t_data	*data ;
	int		off;
	int		full_meals;

	data = (t_data *)arg;
	while (!get_i(&data->r_w, &data->death))
	{
		off = 0;
		// if (get_i(&data->r_w, &data->death) > 0
		// 	|| get_i(&data->r_w, &data->meals_over) == data->nb_philos)
		// {
		// 	clear_if_dead(data);
		// 	off = 1;
		// }
		while (off < data->nb_philos)
		{
			if (!get_i(&data->r_w, &data->philos[off].run))
				set_i(&data->r_w, &data->death, 0);
			off++;
		}
		off = 0;
		full_meals = 0;
		while (off < data->nb_philos && get_i(&data->r_w, &data->philos[off].run))
		{
			full_meals += get_i(&data->r_w, &data->philos[off].nb_of_meal);
			off++;
		}
		if (full_meals == data->meals_max * data->nb_philos)
			break ;
		// usleep(10);
	}
	// printf("FIN\n");
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

void	clear_if_dead(t_data *data)
{
	int	i;

	i = 0;
	if (!pthread_mutex_lock(&data->r_w))
	{
		while (i < data->nb_philos)
		{
			if (!pthread_mutex_lock(&data->over))
			{
				data->philos[i].run = 0;
				pthread_mutex_unlock(&data->over);
			}
			i++;
		}
		pthread_mutex_unlock(&data->r_w);
	}
}
