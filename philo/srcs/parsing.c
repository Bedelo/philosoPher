#include "../includes/philosopher.h"


int	check_digit(char **av)
{
	char	**c;
	int		i;
	int		j;

	i = 1;
	c = av;
	while (c[i])
	{
		while (c[i][j])
		{
			if (!ft_isdigit(c[i][j]))
			{
				write(1, ERROR_DIGIT, 25);
				return (1);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int	check_sign(char **av)
{
	char	**c;
	int		i;

	i = 1;
	c = av;
	while (c[i])
	{
		if (c[i][0] == '-')
		{
			write(1, ERROR_SIGN, 22);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_boundary(char **av)
{
	char	**c;
	int		i;

	i = 1;
	c = av;
	while (c[i])
	{
		if (ft_atol(c[i]) < INT_MIN || ft_atol(c[i]) > INT_MAX)
		{
			write(1, ERROR_BOUND, 15);
			return (1);
		}
		i++;
	}
	return (0);
}



int	parsing(char **av)
{
	if (check_sign(av)|| check_digit(av) || check_boundary(av))
		return (1);
	else
	return (0);
}
