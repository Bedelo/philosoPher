#include "../includes/philosopher.h"

int	use_case_1(t_data *data)
{
	int	res;

	res = 0;
	if (data->nb_philos == 1)
	{
		printf("0\t1\t\tis died\n");
		ft_sleep(data->time_dead);
		res++;
	}
	return (res);
}

static void init_philos(t_data *data)
{
	int		i;

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
}

static void	init_thread(t_data *data)
{
	monitoring_creation(data);
	philos_creation(data);
	data->philo_ready = 1;
	data->time_of_begin = ft_time();
	philos_join(data);
	if (!monitoring_join(data))
	{
		free(data->forks);
		free(data->philos);
	}
}

static void	start0(t_data *data, char **av)
{
	data->nb_philos = ft_atol(av[1]);
	data->time_dead = ft_atol(av[2]);
	if (use_case_1(data))
		return ;
	data->time_eat = ft_atol(av[3]);
	data->time_sleep = ft_atol(av[4]);
	if (av[5])
		data->meals_max = ft_atol(av[5]);
	else
		data->meals_max = -1;
	data->philos = (t_philo *)malloc(data->nb_philos * sizeof(t_philo));
	if (!data->philos)
		return ;
	pthread_mutex_init(&data->printable, NULL);
	pthread_mutex_init(&data->over, NULL);
	data->forks = forks_tab(data->forks, data->nb_philos);
	data->death = 0;
	data->philo_ready = 0;
	data->meals_over = 0;
	init_philos(data);
	init_thread(data);
}


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
		start0(data, av);
		return (SUCCESS);
	}
}
