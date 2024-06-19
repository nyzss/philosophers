/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 07:21:25 by okoca             #+#    #+#             */
/*   Updated: 2024/06/19 09:41:09 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*pl_eating(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pl_lock_forks(philo);
	philo->last_eaten = pl_get_time();
	philo->meal_count += 1;
	usleep(1000 * 100);
	printf("%lld %d is eating\n", pl_get_time() - philo->data->start_time, philo->id);
	pl_unlock_forks(philo);
	return (NULL);
}

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
		philos[i].last_eaten = 0;
		philos[i].meal_count = 0;
		if (pthread_create(&(philos[i].thread_id), NULL, pl_eating, &(philos[i])) != 0)
			return (1);
		i++;
	}
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

t_data	pl_init_data(int ac, char **av)
{
	t_data	data;

	if (ac == 6)
		data.maximum_meal = ft_atoi(av[5]);
	data.nb_philo = ft_atoi(av[1]);
	data.time_to_die = ft_atoi(av[2]);
	data.time_to_eat = ft_atoi(av[3]);
	data.time_to_sleep = ft_atoi(av[4]);
	data.start_time = pl_get_time();
	pl_init_forks(&data);
	return (data);
}

// nb_philo, time_to_die, time_to_eat, time_to_sleep, [max eat]
// 5 800 200 200 7
int main(int ac, char **av)
{
	t_philo		philo[200];
	t_data		data;

	if (pl_parse_args(ac, av) == 1)
		return (1);
	data = pl_init_data(ac, av);
	pl_create_philos(&data, philo);
	pl_destroy_forks(&data);
	printf("hello world!\n");
}
