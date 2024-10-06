#include "../includes/philosopher.h"


void	wait_to_ready(t_data *data)
{
	while (1)
	{
		if (ft_time() > get_ll(&data->r_w, &data->time_of_begin))
			break ;
		usleep(10);
	}
}

static int	check_death(t_philo *philo, t_data *data)
{
	long long	m_time;

	m_time = ft_time();
	if (philo->time_last_meal + data->time_dead < m_time )
	{
		set_i(&data->r_w, &philo->run, 0);
	}

	return (get_i(&data->r_w, &philo->run));
}

static int	full_meals(t_philo *philo, t_data *data)
{
	int	stop;

	stop = 0;
	if (data->meals_max == -1 || philo->nb_of_meal < get_i(&data->r_w, &data->meals_max))
		stop = 0;
	else if (philo->nb_of_meal >= get_i(&data->r_w, &data->meals_max))
	{
		stop = 1;
		//set_i(&data->r_w, &data->meals_over, data->meals_over + 1);
	}
	return (stop);
}


static void	delay(t_philo *philo, t_data *data)
{
	long long	m_time;

	if (philo->name % 2 == 0 && philo->nb_of_meal == 0)
	{
		m_time = ft_time();
		pthread_mutex_lock(&data->printable);
			printf("%lld\t%d\t\tis thinking\n", m_time - data->time_of_begin, philo->name + 1);
		pthread_mutex_unlock(&(data->printable));
		usleep(data->time_eat );
		philo->time_last_meal = ft_time();

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

	philo = (t_philo *)philosophe;
	data = philo->data;
	wait_to_ready(data);
	philo->time_last_meal = data->time_of_begin;
	while (!get_i(&data->over, &data->death) )
	{
		delay(philo, data);
		{
			wait_last_odd(philo, data);
			{
				eating(philo);
				if (check_death(philo, data))
					sleeping_thinking(philo);
			}
			if (full_meals(philo, data))
				break ;
		}
		check_death(philo, data);
		usleep(100);
	}
	return (NULL);
}

void	philos_creation(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_create(&(data->philos[i].phi), NULL, routine, (void *)&((data->philos[i].name)));
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
		i++;
	}
	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
}

pthread_mutex_t	*forks_tab(pthread_mutex_t *tab, int nb_philos)
{
	int				i;

	i = 0;
	tab = malloc(sizeof(pthread_mutex_t) * nb_philos);
	if (!tab)
		return (NULL);
	while (i < nb_philos)
	{
		pthread_mutex_init(&tab[i], NULL);
		i++;
	}
	return (tab);
}
