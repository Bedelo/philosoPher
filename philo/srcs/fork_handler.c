#include "../includes/philosopher.h"

void	lock_fork(t_philo *philo, t_data *data)
{
	int	i;

	i = (philo->name + 1) % data->nb_philos;
	if (philo->name % 2 == 0)
	{
		if (!pthread_mutex_lock(&data->forks[i]))
			print_has_taken_fork(philo, data);
		if (!pthread_mutex_lock(&data->forks[philo->name]))
			print_has_taken_fork(philo, data);
	}
	else
	{
		if (!pthread_mutex_lock(&data->forks[philo->name]))
			print_has_taken_fork(philo, data);
		if (!pthread_mutex_lock(&data->forks[i]))
			print_has_taken_fork(philo, data);
	}
}

void	unlock_fork(t_philo *philo, t_data *data)
{
	int	i;

	i = (philo->name + 1) % data->nb_philos;
	if (philo->name % 2 == 0)
	{
		pthread_mutex_unlock(&data->forks[philo->name]);
		pthread_mutex_unlock(&data->forks[i]);
	}
	else
	{
		pthread_mutex_unlock(&data->forks[i]);
		pthread_mutex_unlock(&data->forks[philo->name]);
	}
}
