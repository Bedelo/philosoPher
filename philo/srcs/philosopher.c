#include "../includes/philosopher.h"

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
			usleep(data->time_eat * 1000);
		}
		pthread_mutex_unlock(&(data->printable));
	}
}

static void	*routine(void *philosophe)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)philosophe;
	data = (t_data *)philo->data;
	delay(philo, data);
	while (!data->death)
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
