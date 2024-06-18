/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 07:21:25 by okoca             #+#    #+#             */
/*   Updated: 2024/06/18 07:40:47 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*task(void *arg)
{
	printf("arg from inside thread number: %d\n", *((int *)arg));
	return (NULL);
}

void	pl_create_threads(int max)
{
	int			i;
	pthread_t	*f_thread;

	i = 0;
	f_thread = malloc(sizeof(pthread_t) * max);
	while (i < max)
	{
		f_thread[i] = pthread_create(&(f_thread[i]), NULL, &task, &i);
		if (f_thread[i] != 0)
		{
			free(f_thread);
			printf("error occured when creating threads, exiting..\n");
			return ;
		}
		i++;
	}
	i = 0;
	while (i < max)
	{
		if (pthread_join(f_thread[i], NULL) != 0)
		{
			free(f_thread);
			printf("join: error, exiting..");
		}
		i++;
	}
	free(f_thread);
	return ;
}

int main(int ac, char **av)
{
	int	i;
	int	max;

	if (ac != 2)
	{
		printf("womp womp\n");
		return (1);
	}
	i = 0;
	max = ft_atoi(av[1]);
	pl_create_threads(max);
	printf("hello world!\n");
}