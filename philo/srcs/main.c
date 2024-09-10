#include "../includes/philosopher.h"

int	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	init(data, ac , av);
	if(!data->monitoring)
		clear_if_dead(data);
	return (0);
}
