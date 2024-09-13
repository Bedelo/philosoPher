#include "../includes/philosopher.h"


void	wait_to_ready(t_data *data)
{
	while (data->philo_ready == 0)
		usleep(100);
}

static int	check_death(t_philo *philo, t_data *data)
{
	long long	m_time;

	m_time = ft_time();
	if (philo->time_last_meal + data->time_dead < m_time)
	{
		philo->run = 0;
		if (!pthread_mutex_lock(&data->over))
			data->death += 1;
		pthread_mutex_unlock(&(data->over));
		if (!pthread_mutex_lock(&data->printable))
			printf("%lld\t%d\t\tdied\n", m_time - data->time_of_begin, philo->name);
		pthread_mutex_unlock(&(data->printable));
	}
	return (philo->run);
}

static int	full_meals(t_philo *philo, t_data *data)
{
	int			stop;

	stop = 0;
	if (philo->nb_of_meal >= data->meals_max)
		stop = 1;
	if (!pthread_mutex_lock(&data->over))
		data->meals_over += 1;
	pthread_mutex_unlock(&data->over);
	return (stop);
}


static void	delay(t_philo *philo, t_data *data)
{
	long long	m_time;

	if (philo->name % 2 == 0 && philo->nb_of_meal == 0)
	{
		m_time = ft_time();
		pthread_mutex_lock(&data->printable);
			printf("%lld\t%d\t\tis sleeping\n", m_time - data->time_of_begin, philo->name);
		pthread_mutex_unlock(&(data->printable));
		usleep(data->time_eat * 1000);
	}
}

static void	wait_last_odd(t_philo *philo, t_data *data)
{
	if (philo->name != data->nb_philos - 1
		&& data->nb_philos % 2 == 1)
		usleep(1);
}
static void	*routine(void *philosophe)
{
	t_philo	*philo;
	t_data	*data;
	int		stop;

	stop = 0;
	philo = (t_philo *)philosophe;
	data = philo->data;
	printf("routine %d\n", philo->name);
	wait_to_ready(data);
	philo->time_last_meal = data->time_of_begin;
	while (!stop)
	{
		delay(philo, data);
		wait_last_odd(philo, data);
		eating(philo);
		sleeping_thinking(philo);
		stop += !check_death(philo, data);
		stop += full_meals(philo, data);
	}
	// if (!pthread_mutex_lock(&data->over))
	// 	data->meals_max += 1;
	// pthread_mutex_unlock(&data->over);
	// while (data->meals_max < data->nb_philos)
	// 	;
	return (philosophe);
}

void	philos_creation(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_create(&(data->philos[i].phi), NULL, routine, (void *)&((data->philos[i].name)));
		usleep(10);
		i++;
	}
	// data->philo_ready = 1;
	// printf("READY :%d\n", data->philo_ready);
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
		i++;
	}
	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
}

pthread_mutex_t	*forks_tab(pthread_mutex_t *tab, int nb_philos, int *ft)
{
	int				i;

	i = 0;
	tab = malloc(sizeof(pthread_mutex_t) * nb_philos);
	if (!tab)
		return (NULL);
	ft = malloc(nb_philos * sizeof(t_philo));
	if (!ft)
		return (NULL);
	if (!tab)
		return (NULL);
	while (i < nb_philos)
	{
		pthread_mutex_init(&tab[i], NULL);
		ft[i] = 0;
		i++;
	}
	return (tab);
}


