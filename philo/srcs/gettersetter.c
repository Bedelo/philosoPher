/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gettersetter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsunda <bsunda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 09:40:00 by bsunda            #+#    #+#             */
/*   Updated: 2024/11/11 09:40:01 by bsunda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

long long	get_ll(pthread_mutex_t *mut, long long *value)
{
	long long	ret;

	pthread_mutex_lock(mut);
	ret = *value;
	pthread_mutex_unlock(mut);
	return (ret);
}

int	get_i(pthread_mutex_t *mut, int *value)
{
	int	ret;

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

// void	set_philo(pthread_mutex_t *mut, t_philo *dst, t_philo *src)
// {
// 	pthread_mutex_lock(mut);
// 	dst = src;
// 	pthread_mutex_unlock(mut);
// }
// t_philo	*get_philo(pthread_mutex_t *mut, t_philo *value)
// {
// 	t_philo	*ret;

// 	pthread_mutex_lock(mut);
// 	ret = value;
// 	pthread_mutex_unlock(mut);
// 	return (ret);
// }
