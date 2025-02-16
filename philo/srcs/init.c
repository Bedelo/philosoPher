/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsunda <bsunda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 09:39:54 by bsunda            #+#    #+#             */
/*   Updated: 2024/11/27 16:52:58 by bsunda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	use_case_1(t_data *data)
{
	int	res;

	res = 0;
	if (data->nb_philos == 1)
	{
		printf("%d\t1\t\thas taken a fork\n", 0);
		printf("%d\t1\t\tis died\n", data->time_dead);
		ft_sleep(data->time_dead);
		res++;
	}
	return (res);
}

static void	init_philos(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->nb_philos)
	{
		data->philos[i].name = i;
		data->philos[i].run = 1;
		data->philos[i].nb_of_meal = 0;
		data->philos[i].time_stash = 0;
		data->philos[i].time_last_meal = data->time_of_begin;
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
	philos_creation(data);
	monitoring_creation(data);
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
	pthread_mutex_init(&data->r_w, NULL);
	pthread_mutex_init(&data->dead_mut, NULL);
	data->forks = forks_tab(data->forks, data->nb_philos);
	data->death = 0;
	data->philo_ready = 0;
	data->meals_over = 0;
	data->first_dead = -1;
	data->time_of_begin = ft_time();
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
		if (ft_atol(av[1]) == 0)
			write(2, "NONE PHILO\n", 11);
		else
			start0(data, av);
		return (SUCCESS);
	}
}
