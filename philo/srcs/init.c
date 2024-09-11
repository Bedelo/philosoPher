#include "../includes/philosopher.h"


void	start(t_data *data)
{
	int			i;

	i = 0;
	while (i < data->nb_philos)
	{
		data->philos[i].name = i;
		data->philos[i].run = 1;
		data->philos[i].nb_of_meal = 0;
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < data->nb_philos)
	{
		data->philos[i].data = data;
		data->philos[i].time_last_meal = data->time_of_begin;
		i++;
	}
	data->death = 0;
	philos_creation(data);
	monitoring_creation(data);
	monitoring_join(data);
	philos_join(data);
}


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
		if (!data->philos)
			return (0);
		if (!pthread_mutex_init(&data->printable, NULL))
			printf("Printable initialized \n");
		if (!pthread_mutex_init(&data->is_dead, NULL))
			printf("is_dead initialized \n");
		data->forks = forks_tab(data->forks, data->nb_philos);
		data->time_of_begin = ft_time();
		data->monitoring = 1;
		data->philo_ready = 0;
		start(data);
		return (SUCCESS);
	}
}

void	clear_if_dead(t_data *data)
{
	philos_detach(data);
	pthread_mutex_destroy(&data->printable);
	pthread_mutex_destroy(&data->is_dead);
	free(data->philos);
	free(data->forks);
}
