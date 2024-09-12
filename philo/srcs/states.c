#include "../includes/philosopher.h"



void	lock_fork_r(t_philo *philo, t_data *data)
{
	int				i;

	i = philo->name;
	{
		if (!pthread_mutex_lock(&data->forks[i]))
		{
			print_has_taken_fork(philo, data);
		}
	}
}

void	lock_fork_l(t_philo *philo, t_data *data)
{
	int				i;
	int				x;
	pthread_mutex_t	fork_1;

	i = philo->name;
	x = (i + 1) % data->nb_philos;
	fork_1 = data->forks[x];
	{
		if (!pthread_mutex_lock(&fork_1))
		{
			print_has_taken_fork(philo, data);
		}
	}
}


void	unlock_forks(t_philo *philo, t_data *data)
{
	int				i;
	pthread_mutex_t	fork_1;

	i = philo->name;
	fork_1 = data->forks[(i + 1) % data->nb_philos];
	pthread_mutex_unlock(&fork_1);
	pthread_mutex_unlock(&data->forks[i]);
}

void	eating(t_philo *philo)
{
	long long	m_time;
	t_data		*data;
	int 		i;

	data = philo->data;
	m_time = ft_time();
	i = (philo->name + 1) % data->nb_philos;
	if (!pthread_mutex_lock(&data->forks[i]))
		print_has_taken_fork(philo, data);
	if (!pthread_mutex_lock(&data->forks[philo->name]))
		print_has_taken_fork(philo, data);
	{
		print_is_eating(philo, data, m_time);
		ft_sleep(data->time_eat);
		philo->time_last_meal = m_time;
		philo->nb_of_meal += 1;
	}
	pthread_mutex_unlock(&data->forks[philo->name]);
	pthread_mutex_unlock(&data->forks[i]);
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
	ft_sleep(50);
}

