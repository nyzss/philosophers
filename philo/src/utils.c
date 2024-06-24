/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 20:12:15 by okoca             #+#    #+#             */
/*   Updated: 2024/06/24 09:27:20 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	pl_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec) * (long long)1000 + (tv.tv_usec) / 1000);
}

int	pl_parse_args(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac != 5 && ac != 6)
	{
		printf("Usage: max_nb_philo, time_to_die, %s\n",
			"time_to_eat, time_to_sleep, [max eat]");
		return (1);
	}
	while (i < ac - 1)
	{
		if (ft_atoi(av[i + 1]) <= 0)
		{
			printf("only positive numbers please.\n");
			return (1);
		}
		i++;
	}
	if (ft_atoi(av[1]) > 200)
	{
		printf("no more than 200 philos please.\n");
		return (1);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int	pl_end_check(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->end_mutex));
	if (philo->data->should_end == 1)
	{
		pthread_mutex_unlock(&(philo->data->end_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(philo->data->end_mutex));
	return (0);
}

int	ft_sleep(t_data *data, int time)
{
	long long	first;

	(void)data;
	first = pl_get_time();
	while (pl_get_time() - first <= time)
	{
		pthread_mutex_lock(&(data->end_mutex));
		if (data->should_end == 1)
		{
			pthread_mutex_unlock(&(data->end_mutex));
			break ;
		}
		pthread_mutex_unlock(&(data->end_mutex));
		usleep(50);
	}
	return (0);
}