#include "../includes/philosopher.h"


int	ft_atoi(const char *str)
{
	int	a;
	int	sign;
	int	res;

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

// void ft_sleep(delay_ms)
// {
// 	long long m_time;

// 	m_time = ft_time();
// 	while()
// 	{

// 	}
// }