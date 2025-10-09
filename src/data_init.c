/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 14:51:42 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/09 14:50:28 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <string.h>

void	init_data(t_data *data, int *tab)
{
	memset(data, 0, sizeof(*data));
	data->nb_philos = tab[0];
	data->time_to_die = tab[1];
	data->time_to_eat = tab[2];
	data->time_to_sleep = tab[3];
	if (tab[4])
		data->nb_meals = tab[4];
	else
		data->nb_meals = -1;
	free(tab);
}
