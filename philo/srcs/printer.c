#include "../includes/philosopher.h"

void	print_has_taken_fork(t_philo *philo, t_data *data)
{
	long long	m_time;
	int			i; 

	i = philo->name;
	m_time = ft_time();
	if (!pthread_mutex_lock(&data->printable))
		printf("%lld\t%d\t\thas taken a fork\n"
			, m_time - ((((t_data *)philo->data)->time_of_begin)), i);
	pthread_mutex_unlock(&data->printable);
}

void	print_is_eating(t_philo *philo, t_data *data)
{
	long long	m_time;
	int			i;

	i = philo->name;
	m_time = ft_time();
	if (!pthread_mutex_lock(&data->printable))
		printf("%lld\t%d\t\tis eating\n", m_time - data->time_of_begin, i);
	pthread_mutex_unlock(&data->printable);
}