#include "../includes/philosopher.h"

void	eating(t_philo *philo)
{
	long long	m_time;
	t_data		*data;


	data = (t_data *)philo->data;
	m_time = ft_time();
	if (take_forks(philo, m_time))
	{
		if (!pthread_mutex_lock(&data->printable))
		{
			m_time = ft_time();
			printf("%lld\t%d\t\tis eating\n", m_time - data->time_of_begin, philo->name);
			pthread_mutex_unlock(&data->printable);
			philo->time_next_meal = m_time + data->time_dead;
			philo->time_last_meal = m_time;
			philo->nb_of_meal += 1;
		}
		pthread_mutex_unlock(philo->fork_1);
		pthread_mutex_unlock(&philo->fork_0);
		usleep(data->time_eat * 1000);
	}
}

void	sleeping(t_philo *philo)
{
	long long	m_time;
	t_data		*data;

	data = ((t_data *)philo->data);
	if (!pthread_mutex_lock(&data->printable))
	{
		m_time = ft_time();
		printf("%lld\t%d\t\tis sleeping\n", m_time - data->time_of_begin, philo->name);
		pthread_mutex_unlock(&data->printable);
	}
	usleep(data->time_sleep * 1000);
}

void	thinking(t_philo *philo)
{
	long long	m_time;
	t_data		*data;

	data = ((t_data *)philo->data);
	if (!pthread_mutex_lock(&data->printable))
	{
		m_time = ft_time();
		printf("%lld\t%d\t\tis thinking\n", m_time - data->time_of_begin, philo->name);
		pthread_mutex_unlock(&data->printable);
	}
}