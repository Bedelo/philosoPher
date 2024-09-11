#include "../includes/philosopher.h"

void	lock_forks(t_philo *philo, t_data *data)
{
	int				i;
	pthread_mutex_t	fork_1;

	i = philo->name;
	if (i == (data->nb_philos - 1))
		fork_1 = data->philos[0].fork_0;
	else
		fork_1 = data->philos[i + 1].fork_0;
	if (!pthread_mutex_lock(&fork_1))
		print_has_taken_fork(philo, data);
	if (!pthread_mutex_lock(&philo->fork_0))
		print_has_taken_fork(philo, data);	
}

void	unlock_forks(t_philo *philo, t_data *data)
{
	int				i;
	pthread_mutex_t	fork_1;

	i = philo->name;
	if (i == (data->nb_philos - 1))
		fork_1 = data->philos[0].fork_0;
	else
		fork_1 = data->philos[i + 1].fork_0;
	pthread_mutex_unlock(&philo->fork_0);
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
	lock_forks(philo, data);
	philo->time_next_meal = m_time + data->time_dead;
	philo->time_last_meal = m_time;
	philo->nb_of_meal += 1;
	print_is_eating(philo, data);
	unlock_forks(philo, data);
	usleep(data->time_eat * 1000);
	return (philo->nb_of_meal - flag);
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
	pthread_mutex_lock(&data->printable);
	m_time = ft_time();
	printf("%lld\t%d\t\tis thinking\n", m_time - data->time_of_begin, philo->name);
	pthread_mutex_unlock(&data->printable);
}
