#include "../includes/philosopher.h"


static void	*m_routine(void *arg)
{
	t_data	*data ;
	int		off;
	int		full_meals;
	int		philos_off;

	data = (t_data *)arg;
	philos_off = 0;
	while (1)
	{
		off = 0;
		while (off < data->nb_philos && !philos_off)
		{
			if (!get_i(&data->r_w, &data->philos[off].run))
			{
				philos_off++;
				break;
			}
			off++;
		}
		if (philos_off > 0)
		{
			set_i(&data->over, &data->death, 1);
			if (!pthread_mutex_lock(&data->printable))
			{

				printf("%lld\t%d\t\tdied\n",
					ft_time() - get_ll(&data->r_w, &data->time_of_begin),
					data->philos[off].name + 1);
				pthread_mutex_unlock(&(data->printable));
			}
			break ;
		}
		ft_sleep(50);
		off = 0;
		philos_off = 0;
		full_meals = 0;
		if (get_i(&data->over, &data->meals_over) == data->nb_philos)
			break ;
	}
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
