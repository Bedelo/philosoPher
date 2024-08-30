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
		data->time_dead = ft_atoi(av[3]);
		data->time_dead = ft_atoi(av[4]);
		if (av[5])
			data->meals_max = ft_atoi(av[5]);
		else
			data->meals_max = -1;
		data->philos = (t_philo *)malloc(data->nb_philos * sizeof(t_philo));
		data->time_of_begin = 0;
		data->monitoring = 1;
		if (!pthread_mutex_init(&data->printable, NULL))
			printf("Printable initialized \n");
		if (!pthread_mutex_init(&data->is_dead, NULL))
			printf("is_dead initialized \n");
		printf("fin init\n");
		start(data);
		return (SUCCESS);
	}
}

void	start(t_data *data)
{
	int			i;
	long long	m_time_begin;

	m_time_begin = ft_time();
	i = 0;
	while (i < data->nb_philos)
	{
		data->philos[i].name = i;
		data->philos[i].run = 1;
		data->philos[i].nb_of_meal = 0;
		data->time_of_begin = m_time_begin;
		if (!pthread_mutex_init(&data->philos[i].fork_0, NULL))
			printf("fork_0 of %d initialized \n", data->philos[i].name);
		i++;
	}
	i = 0;
	while (i < data->nb_philos)
	{
		data->philos[i].data = data;
		i++;
	}
	philos_creation(data);
	philos_join(data);
}


void	clear_if_dead(t_data *data)
{
	philos_detach(data);
	pthread_mutex_destroy(&data->printable);
	pthread_mutex_destroy(&data->is_dead);
	// free each t_philo in data
	free(data->philos);
}