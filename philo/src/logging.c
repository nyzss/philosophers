/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 10:23:17 by okoca             #+#    #+#             */
/*   Updated: 2024/06/23 09:45:47 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	pl_log_util(long long start_t, int id, t_action action)
{
	if (action == SLEEP)
		printf("%lld %d is sleeping\n", start_t, id);
	else if (action == EAT)
		printf("%lld %d is eating\n", start_t, id);
	else if (action == FORK)
		printf("%lld %d has taken a fork\n", start_t, id);
	else if (action == THINK)
		printf("%lld %d is thinking\n", start_t, id);
	return (0);
}

int	pl_log(t_philo *philo, t_action action)
{
	int	end;

	end = 0;
	pthread_mutex_lock(&(philo->meal_mutex));
	if (philo->data->maximum_meal == 0)
	{
		pthread_mutex_unlock(&(philo->meal_mutex));
		return (0);
	}
	pthread_mutex_unlock(&(philo->meal_mutex));
	pthread_mutex_lock(&(philo->data->log_mutex));
	if (action == DIED)
		printf("%lld %d died\n",
			pl_get_time() - philo->data->start_time, philo->id);
	pthread_mutex_lock(&(philo->data->end_mutex));
	if (philo->data->should_end == 1)
		end = 1;
	pthread_mutex_unlock(&(philo->data->end_mutex));
	if (end != 1)
		pl_log_util(pl_get_time() - philo->data->start_time, philo->id, action);
	pthread_mutex_unlock(&(philo->data->log_mutex));
	return (0);
}
