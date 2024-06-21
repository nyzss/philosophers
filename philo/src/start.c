/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:52:05 by okoca             #+#    #+#             */
/*   Updated: 2024/06/21 17:50:25 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	pl_start_philos(t_data *data)
{
	t_philo	philos[200];

	pl_init_philos(data, philos);
	pl_track_philos(data, philos);
	pl_join_philos(data, philos);
	if (data->end_reason == SATIATED)
		printf("All meal eaten!\n");
	return (0);
}

int	pl_check_dead(t_data *data, t_philo *philo, int *finished)
{
	if (pl_get_time() - philo->last_eaten > (data->time_to_die + 30))
	{
		pthread_mutex_lock(&(data->end_mutex));
		if (data->end_reason == 0)
			data->end_reason = DEATH;
		if (data->should_end != 1)
			philo->dead = 1;
		data->should_end = 1;
		pthread_mutex_unlock(&(data->end_mutex));
	}
	if (philo->meal_remaining == 0)
	{
		if (data->end_reason == 0)
			data->end_reason = SATIATED;
		*finished += 1;
	}
	return (0);
}

int	pl_track_philos( t_data *data, t_philo *philos)
{
	int		i;
	int		j;
	int		finished;

	i = 0;
	while (data->should_end != 1)
	{
		j = 0;
		pthread_mutex_lock(&(data->meal_mutex));
		finished = 0;
		while (j < data->nb_philo)
		{
			pl_check_dead(data, &(philos[j]), &finished);
			j++;
		}
		if (finished == data->nb_philo)
		{
			pthread_mutex_lock(&(data->end_mutex));
			data->should_end = 1;
			pthread_mutex_unlock(&(data->end_mutex));
		}
		pthread_mutex_unlock(&(data->meal_mutex));
		usleep(200);
		i++;
	}
	return (0);
}
