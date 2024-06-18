/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 07:21:25 by okoca             #+#    #+#             */
/*   Updated: 2024/06/18 20:11:50 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	pl_get_time(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec) * (long long)1000 + (tv.tv_usec) / 1000);
}

void	*task(void *arg)
{
	t_ctx			*ctx;

	ctx = (t_ctx *)arg;
	pthread_mutex_lock(&(ctx->lock_f));
	usleep(1000 * 100);
	pthread_mutex_unlock(&(ctx->lock_f));
	printf("current_time: %lld\n", pl_get_time() - ctx->start_time);
	return (NULL);
}

void	pl_create_threads(t_ctx *ctx, int max)
{
	int			i;
	pthread_t	*f_thread;
	int			p_r;

	i = 0;
	f_thread = malloc(sizeof(pthread_t) * max);
	while (i < max)
	{
		if (pthread_create(f_thread + i, NULL, task, ctx))
		{
			printf("error occured when creating threads, exiting..\n");
			free(f_thread);
			return ;
		}
		i++;
	}
	i = 0;
	while (i < max)
	{
		p_r = pthread_join(f_thread[i], NULL);
		if (p_r != 0)
		{
			printf("error occured when creating threads, exiting..\n");
			free(f_thread);
			return ;
		}
		i++;
	}
	free(f_thread);
	return ;
}

int	pl_parse_args(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac < 5 || ac > 6)
	{
		printf("not enough arguments\n");
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
}

// nb_philo, time_to_die, time_to_eat, time_to_sleep, [max eat]
// 5 800 200 200 7
int main(int ac, char **av)
{
	int			max;
	t_ctx		ctx;

	if (pl_parse_args(ac, av) == 1)
		return (1);
	ctx.start_time = pl_get_time();
	if (pthread_mutex_init(&(ctx.lock_f), NULL) != 0)
	{
		printf("error when creating mutexes\n");
		return (0);
	}
	max = ft_atoi(av[1]);
	pl_create_threads(&ctx, max);
	pthread_mutex_destroy(&(ctx.lock_f));
	printf("hello world!\n");
}
// number_of_philosophers time_to_die time_to_eat time_to_sleep
// [number_of_times_each_philosopher_must_eat]
