#include "../includes/philosopher.h"

int	lock_forks(t_philo *philo, t_data *data)
{
	int				i;
	int				res;
	pthread_mutex_t	fork_1;

	i = philo->name;
	res = 0;
	if (i == (data->nb_philos - 1))
		fork_1 = data->forks[0];
	else
		fork_1 = data->forks[i + 1];
	if (!pthread_mutex_lock(&fork_1))
	{
		print_has_taken_fork(philo, data);
		res += 1;
	}
	if (!pthread_mutex_lock(&data->forks[i]))
	{
		print_has_taken_fork(philo, data);
		res += 1;
	}
	return (res);
}

void	unlock_forks(t_philo *philo, t_data *data)
{
	int				i;
	pthread_mutex_t	fork_1;

	i = philo->name;
	if (i == (data->nb_philos - 1))
		fork_1 = data->forks[0];
	else
		fork_1 = data->forks[i + 1];
	pthread_mutex_unlock(&data->forks[i]);
	pthread_mutex_unlock(&fork_1);
}

int	eating(t_philo *philo)
{
	long long	m_time;
	t_data		*data;
	int			flag;

	flag = philo->nb_of_meal;
	data = (t_data *)philo->data;
	m_time = ft_time();
	if (lock_forks(philo, data) == 2)
	{
		ft_sleep(data->time_eat);
		philo->time_last_meal = m_time;
		philo->nb_of_meal += 1;
		unlock_forks(philo, data);
	}
	print_is_eating(philo, data, m_time);
	return (philo->nb_of_meal - flag);
}


void	sleeping(t_philo *philo)
{
	long long	m_time;
	t_data		*data;

	data = ((t_data *)philo->data);
	m_time = ft_time();
	if (!pthread_mutex_lock(&data->printable))
	{
		printf("%lld\t%d\t\tis sleeping\n", m_time - data->time_of_begin, philo->name);
		pthread_mutex_unlock(&data->printable);
	}
	ft_sleep(data->time_sleep);
}


void	thinking(t_philo *philo)
{
	long long	m_time;
	t_data		*data;

	data = philo->data;
	m_time = ft_time();
	if (!pthread_mutex_lock(&data->printable))
	{
		printf("%lld\t%d\t\tis thinking\n", m_time - data->time_of_begin, philo->name);
		pthread_mutex_unlock(&data->printable);
	}
}
