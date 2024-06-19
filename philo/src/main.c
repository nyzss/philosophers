/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 07:21:25 by okoca             #+#    #+#             */
/*   Updated: 2024/06/19 15:00:56 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	pl_join_philos(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->data->nb_philo)
	{
		if (pthread_join(philos[i].thread_id, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	pl_check_meal_count(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (philos[i].meal_remaining != 0)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	pl_check_died(t_philo *philos, t_data *data, int *finished)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < data->nb_philo)
	{
		if (philos[i].meal_remaining >= 0 && philos[i].meal_remaining == 0)
			count += 1;
		if (pl_get_time() - philos[i].last_eaten > data->time_to_die)
			return (TRUE);
		i++;
	}
	*finished = count;
	return (FALSE);
}

t_action	pl_check_philos(t_philo *philos, t_data *data)
{
	int	finished;

	finished = 0;
	while (1)
	{
		pthread_mutex_lock(&(philos->data->log_mutex));
		if (pl_check_died(philos, data, &finished) == TRUE)
		{
			return (DIED);
		}
		else if (finished == data->nb_philo)
		{
			data->should_end = 1;
			return (SATISFIED);
		}
		pthread_mutex_unlock(&(philos->data->log_mutex));
	}
	return (0);
}

int	pl_create_philos(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		philos[i].id = i + 1;
		philos[i].data = data;
		philos[i].left_fork = &(philos->data->forks[i]);
		philos[i].right_fork = &(philos->data->forks[(i + 1) % data->nb_philo]);
		philos[i].last_eaten = pl_get_time();
		philos[i].meal_remaining = data->maximum_meal;
		philos[i].dead = FALSE;
		if (pthread_create(&(philos[i].thread_id), NULL, pl_action, &(philos[i])) != 0)
			return (1);
		i++;
	}
	pl_check_philos(philos, data);
	return (pl_join_philos(philos));
}
int		pl_destroy_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_destroy(&(data->forks[i])) != 0)
			return (1);
		i++;
	}
	return (0);

}

int		pl_init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	pl_init_data(t_data *data, int ac, char **av)
{
	t_data	new;

	if (ac == 6)
		new.maximum_meal = ft_atoi(av[5]);
	else
		new.maximum_meal = -1;
	new.nb_philo = ft_atoi(av[1]);
	new.time_to_die = ft_atoi(av[2]);
	new.time_to_eat = ft_atoi(av[3]);
	new.time_to_sleep = ft_atoi(av[4]);
	new.start_time = pl_get_time();
	new.should_end = FALSE;
	if (pl_init_forks(&new) != 0)
		return (1);
	if (pthread_mutex_init(&(new.log_mutex), NULL) != 0)
		return (1);
	if (pthread_mutex_init(&(new.dead_mutex), NULL) != 0)
		return (1);
	*data = new;
	return (0);
}

// nb_philo, time_to_die, time_to_eat, time_to_sleep, [max eat]
// 5 800 200 200 7
int main(int ac, char **av)
{
	t_philo		philo[200];
	t_data		data;

	if (pl_parse_args(ac, av) == 1)
		return (1);
	if (pl_init_data(&data, ac, av) != 0)
		return (1);
	pl_create_philos(&data, philo);
	pl_destroy_forks(&data);
	pthread_mutex_destroy(&(data.log_mutex));
	pthread_mutex_destroy(&(data.dead_mutex));
	printf("hello world!\n");
}
