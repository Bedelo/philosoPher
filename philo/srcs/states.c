/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsunda <bsunda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 09:38:49 by bsunda            #+#    #+#             */
/*   Updated: 2024/11/11 09:53:19 by bsunda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

// void	lock_fork(t_philo *philo, t_data *data)
// {
// 	int	i;

// 	i = (philo->name + 1) % data->nb_philos;
// 	if (philo->name % 2 == 0)
// 	{
// 		if (!pthread_mutex_lock(&data->forks[i]))
// 			print_has_taken_fork(philo, data);
// 		if (!pthread_mutex_lock(&data->forks[philo->name]))
// 			print_has_taken_fork(philo, data);
// 	}
// 	else
// 	{
// 		if (!pthread_mutex_lock(&data->forks[philo->name]))
// 			print_has_taken_fork(philo, data);
// 		if (!pthread_mutex_lock(&data->forks[i]))
// 			print_has_taken_fork(philo, data);
// 	}
// }

// void	unlock_fork(t_philo *philo, t_data *data)
// {
// 	int	i;

// 	i = (philo->name + 1) % data->nb_philos;
// 	if (philo->name % 2 == 0)
// 	{
// 		pthread_mutex_unlock(&data->forks[philo->name]);
// 		pthread_mutex_unlock(&data->forks[i]);
// 	}
// 	else
// 	{
// 		pthread_mutex_unlock(&data->forks[i]);
// 		pthread_mutex_unlock(&data->forks[philo->name]);
// 	}
// }

static int	condition(t_philo *philo, long long m_time)
{
	t_data		*data;
	int			res;

	res = 0;
	data = philo->data;
	if (data->time_dead < data->time_eat)
		res = 1;
	else if (data->time_dead == data->time_eat)
	{
		if (data->time_sleep == data->time_eat)
			res = 1;
	}
	else if (data->time_dead + philo->time_last_meal < m_time)
		res = 1;
	else if (data->time_dead < 2 * data->time_eat && data->nb_philos % 2 == 0)
		res = 2;
	else if (data->time_dead < 3 * data->time_eat && data->nb_philos % 2 == 1)
		res = 2;
	if ((m_time < data->time_of_begin + data->time_eat
			&& res == 2 && data->nb_philos % 2 == 0)
		|| (m_time < data->time_of_begin + 2 * data->time_eat
			&& res == 2 && data->nb_philos % 2 == 1))
		res = 0;
	return (res);
}

void	philo_die(t_philo *philo, int time)
{
	t_data		*data;

	data = philo->data;
	ft_sleep(time);
	set_i(&data->dead_mut, &data->first_dead, philo->name);
}

void	philo_eats(t_philo *philo, t_data *data, int res)
{
	long long	delta;

	delta = 15;
	delta = philo->time_last_meal - data->time_of_begin;
	data = philo->data;
	if (res == 1)
		philo_die(philo, data->time_dead);
	else if (res == 2)
	{
		if (data->nb_philos % 2 == 0)
			philo_die(philo, (data->time_dead - data->time_eat));
		else
			philo_die(philo, data->time_eat
				- (3 * data->time_eat - data->time_dead));
	}
	else
		ft_sleep(data->time_eat);
}

void	eating(t_philo *philo)
{
	t_data		*data;
	long long	m_time;
	int			usecase;

	data = philo->data;
	lock_fork(philo, data);
	m_time = ft_time();
	print_is_eating(philo, data, m_time);
	philo->time_last_meal = m_time;
	usecase = condition(philo, m_time);
	philo_eats(philo, data, usecase);
	philo->nb_of_meal += 1;
	unlock_fork(philo, data);
}

void	sleeping_thinking(t_philo *philo)
{
	t_data		*data;
	long long	m_time;

	data = philo->data;
	m_time = ft_time();
	print_sleeping(philo, data, m_time);
	if (data->time_sleep + data->time_eat > data->time_dead
		&& data->time_eat <= data->time_dead)
	{
		ft_sleep(data->time_dead - data->time_eat);
		set_i(&data->dead_mut, &data->first_dead, philo->name);
	}
	else
		ft_sleep(data->time_sleep);
	usleep(500);
	if (get_i(&data->dead_mut, &data->first_dead) < 0)
	{
		m_time = ft_time();
		print_thinking(philo, data, m_time);
		if (data->nb_philos % 2 == 1)
			ft_sleep(2 * data->time_eat - data->time_sleep);
		else
			ft_sleep(data->time_eat - data->time_sleep);
	}
}

// void	eating(t_philo *philo)
// {
// 	t_data		*data;
// 	long long	m_time;

// 	data = philo->data;
// 	lock_fork(philo, data);
// 	m_time = ft_time();
// 	print_is_eating(philo, data, m_time);
// 	if (2 * data->time_eat <= data->time_dead
// 		&& data->time_eat + data->time_sleep <= data->time_dead
// 		&& data->nb_philos % 2 == 0)
// 	{
// 		ft_sleep(data->time_eat);
// 		philo->time_last_meal = ft_time();
// 	}
// 	else if (2 * data->time_eat > data->time_dead
// 		&& data->time_eat + data->time_sleep <= data->time_dead
// 		&& data->nb_philos % 2 == 0)
// 	{
// 		ft_sleep(data->time_eat);
// 	}
// 	else if (3 * data->time_eat <= data->time_dead
// 		&& data->time_eat + data->time_sleep <= data->time_dead)
// 	{
// 		ft_sleep(data->time_eat);
// 		philo->time_last_meal = ft_time();
// 	}
// 	else
// 	{
// 		ft_sleep( data->time_dead );
// 		set_i(&data->dead_mut, &data->first_dead, philo->name);
// 	}
// 	unlock_fork(philo, data);
// }

// void	sleeping_thinking(t_philo *philo)
// {
// 	t_data		*data;
// 	long long	m_time;

// 	data = philo->data;
// 	if (get_i(&data->dead_mut, &data->first_dead) < 0)
// 	{
// 		m_time = ft_time();
// 		print_sleeping(philo, data, m_time);
// 		if (data->time_eat + data->time_sleep > data->time_dead)
// 		{
// 			ft_sleep(data->time_dead - data->time_eat);
// 			set_i(&data->dead_mut, &data->first_dead, philo->name);
// 		}
// 		else if (2 * data->time_eat > data->time_dead
// 			&& data->time_eat + data->time_sleep <= data->time_dead
// 			&& data->nb_philos % 2 == 0)
// 		{
// 			ft_sleep(data->time_dead - data->time_eat);
// 			set_i(&data->dead_mut, &data->first_dead, philo->name);
// 		}
// 		else
// 		{
// 			ft_sleep(data->time_sleep);
// 			philo->nb_of_meal += 1;
// 		}
// 	}
// 	// usleep(500);
// 	if (get_i(&data->dead_mut, &data->first_dead) < 0)
// 	{
// 		m_time = ft_time();
// 		if(data->nb_philos % 2 == 1 )
// 			ft_sleep(2 * data->time_eat - data->time_sleep);
// 		else
// 			ft_sleep(data->time_eat - data->time_sleep);
// 		print_thinking(philo, data, m_time);
// 	}
// }
