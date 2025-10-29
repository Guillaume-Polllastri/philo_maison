/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_order.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 11:18:07 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/29 13:10:47 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	get_order(int id, int nb_philos)
{
	if (nb_philos == 1)
		return (1);
	else if (id % 2 && id != nb_philos)
		return (1);
	else if (!(id % 2))
		return (2);
	return (3);
}

long long	get_time_to_think(t_philo *philo, t_data *data, bool is_starting)
{
	long long	time_to_think;

	if (is_starting)
		time_to_think = (get_order(philo->id, data->nb_philos) - 1)
			* data->time_to_eat;
	else if (!is_starting && (data->nb_philos % 2))
		time_to_think = 2 * data->time_to_eat - data->time_to_sleep;
	else
		time_to_think = 0;
	return (time_to_think * 1000);
}
