/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_order.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:10:27 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/16 13:48:02 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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

long long	get_time_to_think(t_philo *philo, bool is_starting)
{
	long long	time_to_think;

	if (is_starting)
		time_to_think = (get_order(philo->id, philo->data->nb_philos) - 1)
			* philo->data->time_to_eat;
	else if (!is_starting && (philo->data->nb_philos % 2))
		time_to_think = 2 * philo->data->time_to_eat
			- philo->data->time_to_sleep;
	else
		time_to_think = 0;
	return (time_to_think * 1000);
}
