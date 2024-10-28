#include "../includes/philosopher.h"

void	lock_fork(t_philo *philo, t_data *data)
{
	int i;

	i = (philo->name + 1) % data->nb_philos;
	if (philo->name % 2 == 0)
	{
		if (!pthread_mutex_lock(&data->forks[i]))
			print_has_taken_fork(philo, data);
		if (!pthread_mutex_lock(&data->forks[philo->name]))
			print_has_taken_fork(philo, data);
	}
	else
	{
		if (!pthread_mutex_lock(&data->forks[philo->name]))
			print_has_taken_fork(philo, data);
		if (!pthread_mutex_lock(&data->forks[i]))
			print_has_taken_fork(philo, data);
	}
}

void	unlock_fork(t_philo *philo, t_data *data)
{
	int i;

	i = (philo->name + 1) % data->nb_philos;
	if (philo->name % 2 == 0)
	{
		pthread_mutex_unlock(&data->forks[philo->name]);
		pthread_mutex_unlock(&data->forks[i]);
	}
	else
	{
		pthread_mutex_unlock(&data->forks[i]);
		pthread_mutex_unlock(&data->forks[philo->name]);
	}
}

void	eating(t_philo *philo)
{
	t_data		*data;
	long long	m_time;

	data = philo->data;
	lock_fork(philo, data);
	m_time = ft_time();
	print_is_eating(philo, data, m_time);
	// if (data->time_dead < data-> time_eat)
	// {
	// 	ft_sleep(data->time_dead);
	// 	philo->time_last_meal = m_time;
	// 	// set_i(&data->r_w, &philo->nb_of_meal, philo->nb_of_meal + 1);
	// 	set_i(&data->r_w, &philo->run, 0);
	// }
	// else
	// {
	// 	ft_sleep(data->time_eat);
	// 	philo->time_last_meal = m_time;
	// 	// set_i(&data->r_w, &philo->nb_of_meal, philo->nb_of_meal + 1);
	// }
	if (m_time + data->time_eat < philo->time_last_meal + data->time_dead)
	{
		ft_sleep(data->time_eat);
		set_i(&data->r_w, &philo->nb_of_meal, philo->nb_of_meal + 1);
	}
	// else if (data->time_dead < data->eat)
	// {
	// 	ft_sleep(data->time_dead);
	// 	set
	// }
	else
	{
		ft_sleep(philo->time_last_meal + data->time_dead - m_time);
		set_i(&data->over, &philo->run, 0);
	}
	philo->time_last_meal = ft_time();
	unlock_fork(philo, data);
}

void	sleeping_thinking(t_philo *philo)
{
	t_data		*data;
	long long	m_time;

	data = philo->data;
	if (!get_i(&data->over, &data->death))
	{
		m_time = ft_time();
		print_sleeping(philo, data, m_time);
		// if (data->time_sleep > data->time_dead - data->time_eat)
		if( philo->time_last_meal + data->time_dead
			< m_time + data->time_sleep)
			ft_sleep(philo->time_last_meal + data->time_dead - m_time);
		else
			ft_sleep(data->time_sleep);
	}
	if (!get_i(&data->over, &data->death))
	{
		m_time = ft_time();
		print_thinking(philo, data, m_time);
	}
}
