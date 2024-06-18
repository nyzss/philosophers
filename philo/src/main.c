/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 07:21:25 by okoca             #+#    #+#             */
/*   Updated: 2024/06/18 19:59:51 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	pl_get_time(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return ((tv.tv_sec) * (long long)1000 + (tv.tv_usec) / 1000);
}

// void	*task(void *arg)
// {
// 	t_philo			*ctx;
// 	long long		start;
// 	long long		end;

// 	ctx = (t_philo *)arg;
// 	start = pl_get_time();
// 	printf("start: %lld\n", pl_get_time());
// 	pthread_mutex_lock(&(ctx->lock));
// 	usleep(1000 * 1000);
// 	printf("hello world!!\n");
// 	pthread_mutex_unlock(&(ctx->lock));
// 	end = pl_get_time();
// 	printf("end: %lld\n", pl_get_time());
// 	printf("total time elapsed: %lld\n", end - start);
// 	return (NULL);
// }

void	*task(void *arg)
{
	t_ctx			*ctx;

	ctx = (t_ctx *)arg;
	pthread_mutex_lock(&(ctx->lock_f));
	usleep(1000 * 100);
	// printf("hello world!!\n");
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
// void	*pl_update_time(void *arg)
// {
// 	t_philo		*ctx;

// 	ctx = (t_philo *)arg;
// 	ctx->time = pl_get_time() - ctx->start;
// 	printf("is this getting called anyway? %lld", pl_get_time());
// 	return (NULL);
// }

int main(int ac, char **av)
{
	int			max;
	t_ctx		ctx;

	ctx.start_time = pl_get_time();
	if (ac != 2)
	{
		printf("womp womp\n");
		return (1);
	}
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