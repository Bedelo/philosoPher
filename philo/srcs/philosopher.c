#include "../includes/philosopher.h"

static int	check_death(t_philo *philo, t_data *data)
{
	long long	m_time;

	m_time = ft_time();
	if (philo->time_last_meal + data->time_dead < m_time)
	{
		philo->run = 0;
		if (!pthread_mutex_lock(&data->printable))
			printf("%lld\t%d\t\tdied\n", m_time - data->time_of_begin, philo->name);
		pthread_mutex_unlock(&(data->printable));
	}
	return (philo->run);
}

static int full_meals(t_philo *philo, t_data *data)
{
	long long	m_time;
	int			stop;

	stop = 0;
	m_time = ft_time();
	if (data->meals_max == philo->nb_of_meal)
	{
		stop = 1;
	}
	return (stop);
}


static void	delay(t_philo *philo, t_data *data)
{
	long long	m_time;

	if (philo->name % 2 == 1 && philo->nb_of_meal == 0)
	{
		m_time = ft_time();
		if (!pthread_mutex_lock(&data->printable))
			printf("%lld\t%d\t\tis sleeping\n", m_time - data->time_of_begin, philo->name);
		pthread_mutex_unlock(&(data->printable));
		ft_sleep(50);
	}
}

static void	*routine(void *philosophe)
{
	t_philo	*philo;
	t_data	*data;
	int		stop;

	stop = 0;
	philo = (t_philo *)philosophe;
	data = (t_data *)philo->data;
	while (!stop)
	{
		delay(philo, data);
		if (eating(philo))
		{
			sleeping(philo);
			thinking(philo);
		}
		stop += check_death(philo, data);
		stop +=full_meals(philo, data);
		usleep(50);
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
	data->philo_ready = 1;
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
		pthread_mutex_destroy(&data->forks[i]);
		pthread_detach(data->philos[i].phi);
		i++;
	}
}

pthread_mutex_t	*forks_tab(pthread_mutex_t *tab, int nb_philo)
{
	int				i;

	i = 0;
	tab = malloc(sizeof(pthread_mutex_t) * nb_philo);
	while (i < nb_philo)
	{
		pthread_mutex_init(&tab[i], NULL);
		i++;
	}
	return (tab);
}
