#include "../includes/philosopher.h"

long	ft_atol(const char *str)
{
	long		a;
	long		sign;
	long		res;

	a = 0;
	sign = 1;
	res = 0;
	while (str[a] == ' ' || (str[a] >= '\t' && str[a] <= '\r'))
		a++;
	if (str[a] == '-' || str[a] == '+')
	{
		if (str[a] == '-')
			sign = sign * (-1);
		a++;
	}
	while (str[a] >= '0' && str[a] <= '9')
	{
		res = (res * 10) + (str[a] - '0');
		a++;
	}
	return (res * sign);
}

long long	ft_time(void)
{
	struct timeval	xtv;

	gettimeofday(&xtv, NULL);
	return ((xtv.tv_sec * 1000) + (xtv.tv_usec / 1000));
}

void	ft_sleep(long long delay_ms)
{
	long long	m_time;
	long long	gap;

	m_time = ft_time();
	gap = m_time + delay_ms;
	while (ft_time() < gap)
	{
		usleep(25);
	}
}

int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (c);
	else
		return (0);
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
