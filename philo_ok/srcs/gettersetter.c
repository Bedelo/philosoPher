#include "../includes/philosopher.h"


long long get_ll(pthread_mutex_t *mut, long long *value)
{
	long long ret;
	pthread_mutex_lock(mut);
	ret = *value;
	pthread_mutex_unlock(mut);
	return (ret);
}

int get_i(pthread_mutex_t *mut, int *value)
{
	int ret;
	pthread_mutex_lock(mut);
	ret = *value;
	pthread_mutex_unlock(mut);
	return (ret);
}

t_philo get_phi(pthread_mutex_t *mut, t_philo *value)
{
	t_philo ret;
	pthread_mutex_lock(mut);
	ret = *value;
	pthread_mutex_unlock(mut);
	return (ret);
}

void	set_ll(pthread_mutex_t *mut, long long *dst, long long src)
{
	pthread_mutex_lock(mut);
	*dst = src;
	pthread_mutex_unlock(mut);
}

void	set_i(pthread_mutex_t *mut, int *dst, int src)
{
	pthread_mutex_lock(mut);
	*dst = src;
	pthread_mutex_unlock(mut);
}
