/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:31:02 by okoca             #+#    #+#             */
/*   Updated: 2024/06/19 15:41:49 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_data	data;
	if (pl_parse_args(ac, av) != 0)
		return (1);
	pl_init_data(&data, ac, av);
	pl_init_forks(&data);
	pl_destroy_forks(&data);
}
// nb_philo, time_to_die, time_to_eat, time_to_sleep, [max eat]
// 5 800 200 200 7