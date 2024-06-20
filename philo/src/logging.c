/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:23:17 by okoca             #+#    #+#             */
/*   Updated: 2024/06/20 10:29:40 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	pl_log(t_philo *philo, t_action action)
{
	pthread_mutex_lock(&(philo->data->log_mutex));
	if (action == SLEEP)
		printf("%lld %d is sleeping\n", pl_get_time() - philo->last_eaten, philo->id);
	else if (action == EAT)
		printf("%lld %d is eating\n", pl_get_time() - philo->last_eaten, philo->id);
	else if (action == FORK)
		printf("%lld %d took a fork\n", pl_get_time() - philo->last_eaten, philo->id);
	else if (action == DROP)
		printf("%lld %d dropped a fork\n", pl_get_time() - philo->last_eaten, philo->id);
	pthread_mutex_unlock(&(philo->data->log_mutex));
	return (0);
}
