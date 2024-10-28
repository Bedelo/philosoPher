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
# define ERROR_DIGIT "ONLY DIGITS ARE REQUIRED\n"
# define ERROR_SIGN "NEGATIF SIGN FORBIDEN\n"
# define ERROR_BOUND "BOUNDARY ERROR\n"

typedef struct s_data t_data;

typedef struct s_philo
{
	int					name;
	t_data				*data;
	long long			time_last_meal;
	int					nb_of_meal;
	int					run;
	pthread_t			phi;
	int					time_stash;
}	t_philo;

typedef struct s_data
{
	int					nb_philos;
	int					time_dead;
	int					time_eat;
	int					time_sleep;
	int					meals_max;
	t_philo				*philos;
	pthread_t			monitoring_t;
	pthread_mutex_t		printable;
	pthread_mutex_t		*forks;
	pthread_mutex_t		over;
	pthread_mutex_t		r_w;
	int					barrier;
	int					meals_over;
	int					death;
	long long			time_of_begin;
	int					philo_ready;
}	t_data;

//synchroniser data pour les philo lors de lutilisation
//ressource partager pour les thread avec printable


pthread_mutex_t	*forks_tab(pthread_mutex_t *tab, int nb_philo);
int				init(t_data	*data, int ac, char **av);
void			start(t_data *data);
void			clear_if_dead(t_data *data);

int				take_forks(t_philo *philo, long long time);
void			philos_creation(t_data *data);
void			philos_join(t_data *data);
void			philos_detach(t_data *data);

long			ft_atol(const char *str);
long long		ft_time(void);
void			ft_sleep(long long delay_ms);
int				ft_isdigit(int c);
int				parsing(char **av);

void			print_thinking(t_philo *philo, t_data *data, long long m_time);
void			print_sleeping(t_philo *philo, t_data *data, long long m_time);
void			print_has_taken_fork(t_philo *philo, t_data *data);
void			print_is_eating(t_philo *philo, t_data *data, long long m_time);

void			monitoring_creation(t_data *data);
int				monitoring_join(t_data *data);

void			eating(t_philo *philo);
void			sleeping_thinking(t_philo *philo);
void			thinking(t_philo *philo);

long long		get_ll(pthread_mutex_t *mut, long long *value);
int				get_i(pthread_mutex_t *mut, int *value);
void			set_ll(pthread_mutex_t *mut, long long *dst, long long src);
void			set_i(pthread_mutex_t *mut, int *dst, int src);

#endif
