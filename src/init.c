/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 14:51:42 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/05 17:54:24 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->print, NULL) || pthread_mutex_init(&data->death, NULL))
		return (0);
	return (1);
}

int	setup_data(t_data *data, int *tab)
{
	data->nb_philos = tab[0];
	data->time_to_die = tab[1];
	data->time_to_eat = tab[2];
	data->time_to_sleep = tab[3];
	if (tab[4])
		data->nb_meals = tab[4];
	if (!init_mutex(data))
		return (0);
	return (1);
}
