/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_reaper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 16:17:45 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/15 12:44:20 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdio.h>

void	*routine_death_handler(void *arg)
{
	t_philo		*philos;
	int			i;
	long long	time;
	long long	min;
	int			all_dead;

	philos = (t_philo *)arg;
	all_dead = 0;
	while (is_game_running(philos->data) && !all_dead)
	{
		min = philos->data->time_to_die;
		i = 0;
		all_dead = 1;
		while (i < philos->data->nb_philos)
		{
			all_dead = all_dead & !is_philo_alive(&philos[i]);
			time = get_timestamp() - get_last_meal_time(&philos[i]);
			if (time >= philos->data->time_to_die && is_philo_alive(&philos[i]))
			{
				print_philo_status(&philos[i], "died");
				set_death_status(&philos[i]);
				stop_game(philos->data);
			}
			else
				min = min_value(philos->data->time_to_die - time, min);
			i++;
		}
		// printf("all dead %d\n", all_dead);
		safe_usleep(min * 1000);
	}
	return (NULL);
}
