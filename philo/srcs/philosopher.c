/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsunda <bsunda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 09:39:07 by bsunda            #+#    #+#             */
/*   Updated: 2024/11/11 09:46:13 by bsunda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

static int	full_meals(t_philo *philo, t_data *data)
{
	int	stop;

	stop = 0;
	if (philo->nb_of_meal == data->meals_max)
	{
		usleep(100);
		pthread_mutex_lock(&data->over);
		data->meals_over = data->meals_over + 1;
		pthread_mutex_unlock(&data->over);
		stop = 1;
	}
	return (stop);
}

static void	*routine(void *philosophe)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)philosophe;
	data = philo->data;
	while (get_i(&data->dead_mut, &data->first_dead) < 0)
	{
		eating(philo);
		sleeping_thinking(philo);
		if (full_meals(philo, data))
			break ;
	}
	return (NULL);
}

void	philos_creation(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_create(&(data->philos[i].phi), NULL, routine,
			(void *)&((data->philos[i].name)));
		i++;
	}
}

void	philos_join(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_join(data->philos[i].phi, NULL);
		i++;
	}
}

void	philos_detach(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_detach(data->philos[i].phi);
		i++;
	}
	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
}
