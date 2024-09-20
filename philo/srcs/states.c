#include "../includes/philosopher.h"


void	eating(t_philo *philo)
{
	long long	m_time;
	t_data		*data;
	int 		i;

	data = philo->data;
	m_time = ft_time();
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
	{
		print_is_eating(philo, data, m_time);
		ft_sleep(data->time_eat);
		philo->time_last_meal = m_time;
		set_i(&data->r_w, &philo->nb_of_meal, philo->nb_of_meal + 1);
	}
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


void	sleeping_thinking(t_philo *philo)
{
	long long	m_time;
	t_data		*data;

	data = philo->data;
	m_time = ft_time();
	print_sleeping(philo, data, m_time);
	ft_sleep(data->time_sleep);
	m_time = ft_time();
	print_thinking(philo, data, m_time);
}

