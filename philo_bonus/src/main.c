/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:55:23 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/29 13:12:15 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"
#include <stdio.h>

int	main(int ac, char **av)
{
	int		*tab;
	t_data	data;

	if (ac < 5 || ac > 6)
	{
		printf("Error\nUsage: ./philo nb_philos time_to_die time_to_eat"
			" time_to_sleep [nb_meals]\n");
		return (1);
	}
	tab = parse_args(av);
	if (!tab)
		return (1);
	if (!init_data(&data, tab, ac - 1))
		return (1);
	deploy_philos(&data);
	return (0);
}
