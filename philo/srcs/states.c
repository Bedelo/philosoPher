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
	// if (m_time + data->time_eat <= philo->time_last_meal + data->time_dead)
	// if (philo->time_last_meal - data->time_eat + data->time_dead >= m_time + data->time_eat)
	if (2 * data->time_eat <= data->time_dead
		&& data->time_eat + data->time_sleep <= data->time_dead
		&& data->nb_philos % 2 == 0)
	{
		ft_sleep(data->time_eat);
		philo->time_last_meal = ft_time();
	}
	else if (3 * data->time_eat <= data->time_dead
		&& data->time_eat + data->time_sleep <= data->time_dead)
	{
		ft_sleep(data->time_eat);
		philo->time_last_meal = ft_time();
	}
	else
	{
		ft_sleep( data->time_dead );
		set_i(&data->dead_mut, &data->first_dead, philo->name);
	}
	unlock_fork(philo, data);
}

void	sleeping_thinking(t_philo *philo)
{
	t_data		*data;
	long long	m_time;

	data = philo->data;
	if (get_i(&data->dead_mut, &data->first_dead) < 0)
	{
		m_time = ft_time();
		print_sleeping(philo, data, m_time);
		if (data->time_eat + data->time_sleep > data->time_dead)
		{
			ft_sleep(data->time_dead - data->time_eat);
			set_i(&data->dead_mut, &data->first_dead, philo->name);
		}
		else
		{
			ft_sleep(data->time_sleep);
			philo->nb_of_meal += 1;
		}
	}
	// usleep(500);
	if (get_i(&data->dead_mut, &data->first_dead) < 0)
	{
		m_time = ft_time();
		if(data->nb_philos % 2 == 1 )
			ft_sleep(2 * data->time_eat - data->time_sleep);
		else
			ft_sleep(data->time_eat - data->time_sleep);
		print_thinking(philo, data, m_time);
	}
}
