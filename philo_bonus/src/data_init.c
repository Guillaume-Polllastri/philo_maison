/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:50:59 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/20 12:51:41 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"
#include <stdlib.h>
#include <string.h>

void	init_data(t_data *data, int *tab, int tab_len)
{
	memset(data, 0, sizeof(*data));
	data->nb_philos = tab[0];
	data->time_to_die = tab[1];
	data->time_to_eat = tab[2];
	data->time_to_sleep = tab[3];
	if (tab_len == 5)
		data->nb_meals = tab[4];
	else
		data->nb_meals = -1;
	free(tab);
}