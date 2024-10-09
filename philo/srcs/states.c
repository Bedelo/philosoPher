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
	long long	m_time;
	t_data		*data;
	int 		i;

	data = philo->data;
	m_time = ft_time();
	i = (philo->name + 1) % data->nb_philos;
	lock_fork(philo, data);
	print_is_eating(philo, data, m_time);
	if (data->time_dead > data-> time_eat)
	{
		ft_sleep(data->time_eat);
		philo->time_last_meal = m_time;
		set_i(&data->r_w, &philo->nb_of_meal, philo->nb_of_meal + 1);
	}
	else
	{
		ft_sleep(data->time_dead);
		set_i(&data->r_w, &philo->run, 0);
		set_i(&data->r_w, &philo->nb_of_meal, philo->nb_of_meal + 1);
	}
	unlock_fork(philo, data);
}

void	sleeping_thinking(t_philo *philo)
{
	long long	m_time;
	t_data		*data;

	data = philo->data;
	m_time = ft_time();
	if (!get_i(&data->over, &data->death))
	{
		if (data->time_sleep > data->time_dead - data->time_eat)
			ft_sleep(data->time_dead - data->time_eat);
		else
			ft_sleep(data->time_sleep);
		print_sleeping(philo, data, m_time);
	}
	if (!get_i(&data->over, &data->death))
	{
		// m_time = ft_time();
		print_thinking(philo, data, m_time);
		if (philo->time_stash + data->time_sleep < data->time_eat)
		{
			ft_sleep(philo->time_stash);
			set_i(&data->r_w, &philo->run, 0);
		}
	}
}
