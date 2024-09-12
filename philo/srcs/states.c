#include "../includes/philosopher.h"



void	lock_fork_r(t_philo *philo, t_data *data)
{
	int				i;

	i = philo->name;
	if (!philo->fork_taken || philo->fork_taken % 2 == 0)
	{
		if (!pthread_mutex_lock(&data->forks[i]))
		{
			print_has_taken_fork(philo, data);
			philo->fork_taken += 1;
		}
	}
}

void	lock_fork_l(t_philo *philo, t_data *data)
{
	int				i;
	pthread_mutex_t	fork_1;

	i = philo->name;
	// if (i == (data->nb_philos - 1))
	// 	fork_1 = data->forks[0];
	// else
		fork_1 = data->forks[(i + 1) % data->nb_philos];
	if (!philo->fork_taken || philo->fork_taken < 10)
	{
		if (!pthread_mutex_lock(&fork_1))
		{
			print_has_taken_fork(philo, data);
			philo->fork_taken += 10;
		}
	}
}


void	unlock_forks(t_philo *philo, t_data *data)
{
	int				i;
	pthread_mutex_t	fork_1;

	i = philo->name;
	fork_1 = data->forks[(i + 1) % data->nb_philos];
	if (!pthread_mutex_unlock(&fork_1))
		philo->fork_taken -= 10;
	if (!pthread_mutex_unlock(&data->forks[i]))
		philo->fork_taken -= 1;
}

int	eating(t_philo *philo)
{
	long long	m_time;
	t_data		*data;
	int			flag;

	flag = philo->nb_of_meal;
	data = (t_data *)philo->data;
	m_time = ft_time();
	lock_fork_l(philo, data);
	lock_fork_r(philo, data);
	if (philo->fork_taken == 11)
	{
		print_is_eating(philo, data, m_time);
		ft_sleep(data->time_eat);
		philo->time_last_meal = m_time;
		philo->nb_of_meal += 1;
		unlock_forks(philo, data);
		printf("%d\tstatus take %d\n", philo->name, philo->fork_taken);
	}
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
