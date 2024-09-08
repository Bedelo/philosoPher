#include "../includes/philosopher.h"

int	init(t_data *data, int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		write(1, ERROR_ARGS, 26);
		return (FAILURE);
	}
	else
	{
		data->nb_philos = ft_atoi(av[1]);
		data->time_dead = ft_atoi(av[2]);
		data->time_eat = ft_atoi(av[3]);
		data->time_sleep = ft_atoi(av[4]);
		if (av[5])
			data->meals_max = ft_atoi(av[5]);
		else
			data->meals_max = -1;
		data->philos = (t_philo *)malloc(data->nb_philos * sizeof(t_philo));
		if (pthread_mutex_init(&data->printable, NULL))
			return (FAILURE);
		if (pthread_mutex_init(&data->is_dead, NULL))
			return (FAILURE);
		data->time_of_begin = ft_time();
		data->monitoring = 1;
		if(start(data))
			return (FAILURE);
		return (SUCCESS);
	}
}

// void	fork_assignation(t_data* data)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data->nb_philos - 1)
// 	{
// 		(data->philos[i].fork_1) = &(data->philos[i + 1].fork_0);
// 		i++;
// 	}
// 	(data->philos[data->nb_philos - 1].fork_1) = &(data->philos[0].fork_0);
// }

int	start(t_data *data)
{
	int			i;

	i = 0;
	while (i < data->nb_philos)
	{
		data->philos[i].name = i;
		data->philos[i].run = 1;
		data->philos[i].nb_of_meal = 0;
		if(pthread_mutex_init(&data->philos[i].fork_0, NULL))
			return (FAILURE);
		i++;
	}
	i = 0;
	while (i < data->nb_philos)
	{
		data->philos[i].time_next_meal = data->time_dead + data->time_of_begin;
		data->philos[i].time_last_meal = data->time_of_begin;
		data->philos[i].data = data;
		i++;
	}
	data->death = 0;
	// fork_assignation(data);
	philos_creation(data);
	philos_join(data);
	return (SUCCESS);
}


void	clear_if_dead(t_data *data)
{
	philos_detach(data);
	pthread_mutex_destroy(&data->printable);
	pthread_mutex_destroy(&data->is_dead);
	// free each t_philo in data
	free(data->philos);
}
