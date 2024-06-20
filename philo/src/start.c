/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:52:05 by okoca             #+#    #+#             */
/*   Updated: 2024/06/20 09:19:55 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	pl_track_philos( t_data *data, t_philo *philos)
{
	int		i;
	int		j;

	i = 0;
	while (i < data->maximum_meal + 1)
	{
		j = 0;
		printf("data: %d\n", data->should_end);
		printf("max meal: %d\n", data->maximum_meal);
		while (j < data->nb_philo)
		{
			printf("%lld -> %d - last eaten: %lld\n", pl_get_time() - data->start_time, philos[j].id,  pl_get_time() - philos[j].last_eaten);
			j++;
		}
		usleep(1000 * data->time_to_eat);
		i++;
	}
	return (0);
}

int	pl_start_philos(t_data *data)
{
	t_philo	philos[200];

	pl_init_philos(data, philos);
	pl_track_philos(data, philos);
	pl_join_philos(data, philos);
	return (0);
}
