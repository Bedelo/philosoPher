#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

# define SUCCESS 0
# define FAILURE 1
# define INT_MAX 2147483647
# define INT_MIN -2147483648
# define ERROR_ARGS "SIZE OF ARGS IS INCORRECT\n"

typedef struct s_philo
{
	int					name;
	pthread_t 			phi;
	pthread_mutex_t		fork_0;
	pthread_mutex_t		*fork_1;
	void				*data;
	long long			time_next_meal;
	int					nb_of_meal;
	int					run;
}	t_philo;

typedef struct s_data
{
	int					nb_philos;
	int					time_dead;
	int					time_eat;
	int 				time_sleep;
	int					meals_max;	
	t_philo				*philos;
	pthread_mutex_t		printable;
	pthread_mutex_t		is_dead;
	int					monitoring;
	long long			time_of_begin;
}	t_data;

//synchroniser data pour les philo lors de lutilisation
//ressource partager pour les thread avec printable


int			init(t_data	*data, int ac, char **av);
void		start(t_data *data);
void		clear_if_dead(t_data *data);

int			take_forks(t_philo *philo);
void		philos_creation(t_data *data);
void		philos_join(t_data *data);
void		philos_detach(t_data *data);

int			ft_atoi(const char *str);
long long	ft_time(void);

void		eating(t_philo *philo);
void		sleeping(t_philo *philo);
void		thinking(t_philo *philo);

#endif