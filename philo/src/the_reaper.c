/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_reaper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 16:17:45 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/17 13:43:30 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdio.h>
#include <unistd.h>

static void	check_death_of_philos(t_philo *philos, int *all_dead,
		long long *min)
{
	int			i;
	long long	time;

	i = 0;
	while (i < philos->data->nb_philos)
	{
		*all_dead = *all_dead & !is_philo_alive(&philos[i]);
		time = get_timestamp() - get_last_meal_time(&philos[i]);
		if (time >= philos->data->time_to_die && is_philo_alive(&philos[i]))
		{
			print_philo_status(&philos[i], "died");
			set_death_status(&philos[i]);
			stop_game(philos->data);
		}
		else
			*min = min_value(philos->data->time_to_die - time, *min);
		i++;
	}
}

void	*routine_death_handler(void *arg)
{
	t_philo		*philos;
	long long	min;
	int			all_dead;

	philos = (t_philo *)arg;
	all_dead = 0;
	while (is_game_running(philos->data) && !all_dead)
	{
		min = philos->data->time_to_die;
		all_dead = 1;
		check_death_of_philos(philos, &all_dead, &min);
		safe_usleep(min * 1000);
	}
	return (NULL);
}
