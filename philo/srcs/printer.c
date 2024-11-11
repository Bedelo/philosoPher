/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsunda <bsunda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 09:38:58 by bsunda            #+#    #+#             */
/*   Updated: 2024/11/11 09:38:59 by bsunda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	print_has_taken_fork(t_philo *philo, t_data *data)
{
	long long	m_time;
	int			i;

	i = philo->name;
	m_time = ft_time();
	if (get_i(&data->dead_mut, &data->first_dead) < 0)
	{
		if (!pthread_mutex_lock(&data->printable))
			printf("%-7lld %-7d has taken a fork\n",
				m_time - get_ll(&data->r_w, &data->time_of_begin),
				i + 1);
		pthread_mutex_unlock(&data->printable);
	}
}

void	print_is_eating(t_philo *philo, t_data *data, long long m_time)
{
	int			i;

	i = philo->name;
	m_time = ft_time();
	if (get_i(&data->dead_mut, &data->first_dead) < 0)
	{
		if (!pthread_mutex_lock(&data->printable))
			printf("%-7lld %-7d is eating\n",
				m_time - get_ll(&data->r_w, &data->time_of_begin),
				i + 1);
		pthread_mutex_unlock(&data->printable);
	}
}

void	print_sleeping(t_philo *philo, t_data *data, long long m_time)
{
	int			i;

	i = philo->name;
	if (get_i(&data->dead_mut, &data->first_dead) < 0)
	{
		if (!pthread_mutex_lock(&data->printable))
			printf("%-7lld %-7d is sleeping\n",
				m_time - get_ll(&data->r_w, &data->time_of_begin),
				i + 1);
		pthread_mutex_unlock(&data->printable);
	}
}

void	print_thinking(t_philo *philo, t_data *data, long long m_time)
{
	int			i;

	(void)m_time;
	i = philo->name;
	if (get_i(&data->dead_mut, &data->first_dead) < 0)
	{
		if (!pthread_mutex_lock(&data->printable))
		{
			printf("%-7lld %-7d is thinking\n",
				m_time - get_ll(&data->r_w, &data->time_of_begin),
				i + 1);
		}
		pthread_mutex_unlock(&data->printable);
	}
}
