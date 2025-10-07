/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:39:45 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/07 15:16:16 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include "philo.h"

int	main(int ac, char **av)
{
	int		*tab;
	t_data	data;

	if (ac < 5 || ac > 6)
	{
		printf("Error\nUsage: ./philo nb_philos time_to_die time_to_eat time_to_sleep [nb_meals]\n");
		return (1);
	}
	tab = parse_args(av);
	if (!tab)
		return (1);
	init_data(&data, tab);
	deploy_philos(&data);
	return (0);
}
