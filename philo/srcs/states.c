#include "../includes/philosopher.h"


void eating(t_philo *philo)
{
	long long	m_time;
	t_data		*data;

	data = philo->data;

	pthread_mutex_lock(philo->fork_1);
	pthread_mutex_lock(&philo->fork_0);
	
	// if (take_forks(philo))
	{
		if (!pthread_mutex_lock(&data->printable))
		{
			m_time = ft_time();
			printf("%lld\t\t%d\t\tis eating ", m_time - data->time_of_begin, philo->name);
			pthread_mutex_unlock(&data->printable);
			sleep(data->time_eat);
			philo->time_next_meal = m_time + data->time_eat;
			philo->nb_of_meal += 1; 
		}
		pthread_mutex_unlock(philo->fork_1);
		pthread_mutex_unlock(&philo->fork_0);
	}
}

void sleeping(t_philo *philo)
{
	long long	m_time;
	t_data		*data;

	data = ((t_data *)philo->data);
	if (!pthread_mutex_lock(&data->printable))
	{
		m_time = ft_time();
		printf("%lld\t\t%d\t\tis sleeping ",  m_time - data->time_of_begin, philo->name);
		pthread_mutex_unlock(&data->printable);
		sleep(data->time_sleep);
	}
}

void thinking(t_philo *philo)
{
	long long	m_time;
	t_data		*data;

	data = ((t_data *)philo->data);
	if (!pthread_mutex_lock(&data->printable))
	{
		m_time = ft_time();
		printf("%lld\t\t%d\t\tis thinking ",  m_time - data->time_of_begin, philo->name);
		pthread_mutex_unlock(&data->printable);
	}
}