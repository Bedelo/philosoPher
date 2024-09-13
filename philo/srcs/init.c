#include "../includes/philosopher.h"



int	init(t_data *data, int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		write(1, ERROR_ARGS, 26);
		return (FAILURE);
	}
	else if (parsing(av))
		return (FAILURE);
	else
	{

		data->nb_philos = ft_atol(av[1]);
		data->time_dead = ft_atol(av[2]);
		data->time_eat = ft_atol(av[3]);
		data->time_sleep = ft_atol(av[4]);
		if (av[5])
			data->meals_max = ft_atol(av[5]);
		else
			data->meals_max = -1;
		data->philos = (t_philo *)malloc(data->nb_philos * sizeof(t_philo));
		if (!data->philos)
			return (0);
		pthread_mutex_init(&data->printable, NULL);
		pthread_mutex_init(&data->is_dead, NULL);
		pthread_mutex_init(&data->over, NULL);
		data->forks = forks_tab(data->forks, data->nb_philos, data->fork_taken);
		// data->monitoring = 1;
		data->death = 0;
		data->philo_ready = 0;
		data->meals_over = 0;
		start(data);
		return (SUCCESS);
	}
}



void	start(t_data *data)
{
	int			i;

	i = 0;
	while (i < data->nb_philos)
	{
		data->philos[i].name = i;
		data->philos[i].run = 1;
		data->philos[i].nb_of_meal = 0;
		i++;
	}
	i = 0;
	while (i < data->nb_philos)
	{
		data->philos[i].data = data;
		i++;
	}
	philos_creation(data);
	monitoring_creation(data);
	data->philo_ready = 1;
	data->time_of_begin = ft_time();
	printf("READY :%d\n", data->philo_ready);
	philos_join(data);
	monitoring_join(data);
}


