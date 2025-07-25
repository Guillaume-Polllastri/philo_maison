/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:39:45 by gpollast          #+#    #+#             */
/*   Updated: 2025/07/25 14:45:45 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include "philo.h"

int	main(int ac, char **av)
{
	int	*tab;

	if (ac == 5 || ac == 6)
	{
		tab = parse_args(av);
		if (!tab)
		{
			write(2, "Error\nArgs must be a positive numbers\n", 38);
			return (1);
		}
		printf("Number of philosophers : %d\n", tab[0]);
		printf("Time to die : %d\n", tab[1]);
		printf("Time to eat : %d\n", tab[2]);
		printf("Time to sleep : %d\n", tab[3]);
		if (ac == 6)
			printf("Number of times each philosophers must eat : %d\n", tab[4]);
		free(tab);
	}
	else
		write(2, "Error\nThe program needs 5 arguments\n", 36);
	return (0);
}
