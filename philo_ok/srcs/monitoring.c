#include "../includes/philosopher.h"


// static void	*m_routine(void *arg)
// {
// 	t_data	*data ;
// 	int		off;
// 	int		full_meals;
// 	int		philos_off;
// 	t_philo	philosophe;

// 	data = (t_data *)arg;
// 	philos_off = 0;
// 	while (1)
// 	{
// 		off = 0;
// 		while (off < data->nb_philos && !philos_off)
// 		{
// 			philosophe = get_phi(&data->r_w, &data->philos[off]);
// 			if (!get_i(&data->r_w, &(philosophe.run)))
// 			{
// 				philos_off++;
// 				break;
// 			}
// 			off++;
// 		}
// 		if (philos_off > 0)
// 		{
// 			set_i(&data->over, &data->death, 1);
// 			if (!pthread_mutex_lock(&data->printable))
// 			{

// 				printf("%lld\t%d\t\tdied\n",
// 					ft_time() - get_ll(&data->r_w, &data->time_of_begin),
// 					data->philos[off].name + 1);
// 				pthread_mutex_unlock(&(data->printable));
// 			}
// 			break ;
// 		}
// 		// ft_sleep(25);
// 		off = 0;
// 		philos_off = 0;
// 		full_meals = 0;
// 		if (get_i(&data->over, &data->meals_over) == data->nb_philos)
// 			break ;
// 	}
// 	return (NULL);
// }



static void	*m_routine(void *arg)
{
	t_data	*data ;
	int		id_dead;
	int		i;
	int		stop;

	i = 0;
	data = (t_data *)arg;
	while (1)
	{
		usleep(50);
		id_dead = get_i(&data->dead_mut, &data->first_dead);
		if (id_dead >= 0)
		{
			set_i(&data->over, &data->death, 1);
			pthread_mutex_lock(&data->printable);
			{
				printf("%lld\t%d\t\tdied\n",
					ft_time() - get_ll(&data->r_w, &data->time_of_begin),
					data->philos[id_dead].name + 1);
			}
			pthread_mutex_unlock(&(data->printable));
			break ;
		}

		if (data->meals_max == get_i(&data->r_w, &data->meals_over))
			break;
		// stop = 0;
		// while (i < data->nb_philos)
		// 	stop += get_i(&data->r_w, &data->philos[i].nb_of_meal);
		// if (stop == data->nb_philos * data->meals_max)
		// 		break ;

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
