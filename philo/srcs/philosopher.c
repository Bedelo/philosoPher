#include "../includes/philosopher.h"


int	take_forks(t_philo *philo, long long m_time)
{
	int		i;
	t_data	*data;

	data = (t_data *)philo->data;
	i = philo->name;
	if (i == ((t_data *)philo->data)->nb_philos - 1)
		philo->fork_1 = &((t_data *)philo->data)->philos[0].fork_0;
	else
		philo->fork_1 = &((t_data *)philo->data)->philos[i + 1].fork_0;
	if (!pthread_mutex_lock(&philo->fork_0) || !pthread_mutex_lock(philo->fork_1))
	{
		pthread_mutex_lock(&data->printable);
		printf("%lld\t%d\t\thas taken a fork\n", m_time - ((((t_data *)philo->data)->time_of_begin)), philo->name);
		pthread_mutex_unlock(&data->printable);
		return (1);
	}
	return (0);
}

static int	check_monitoring(t_philo *philo, t_data *data)
{
	long long	m_time;
	int			flag;

	if (!pthread_mutex_lock(&(data->is_dead)))
	{
		m_time = ft_time();
		if (data->meals_max == -1)
			flag = 1;
		else
			flag = data->meals_max - philo->nb_of_meal;
		if (m_time > philo->time_next_meal || flag < 0)
			data->monitoring = 0;
		if (!data->monitoring)
			data->death = 1;
	}
	pthread_mutex_unlock(&(data->is_dead));
	return (data->death);
}

static void	delay(t_philo *philo, t_data *data)
{
	long long	m_time;

	if (philo->name % 2 == 1 && philo->nb_of_meal == 0)
	{
		if (!pthread_mutex_lock(&data->printable))
		{
			m_time = ft_time();
			printf("%lld\t%d\t\tis sleeping\n", m_time - data->time_of_begin, philo->name);
			pthread_mutex_unlock(&data->printable);
		}
		pthread_mutex_unlock(&(data->printable));
		usleep(data->time_eat * 1000);
	}
}

static void	*routine(void *philosophe)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)philosophe;
	data = (t_data *)philo->data;
	delay(philo, data);
	while (1)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
		check_monitoring(philo, data);
		
	}
	return (philosophe);
}

void	philos_creation(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_create(&(data->philos[i].phi), NULL, &routine, (void *)&((data->philos[i].name)));
		i++;
	}
}

void	philos_join(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_join(data->philos[i].phi, NULL);
		i++;
	}
}

void	philos_detach(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_detach(data->philos[i].phi);
		pthread_mutex_destroy(&data->philos[i].fork_0);
		i++;
	}
}