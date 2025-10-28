/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atomic.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 13:19:09 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/28 17:16:45 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <stdio.h>

void	print_philo_status(t_philo *philo, t_data *data, char *s)
{
	sem_wait(data->print);
	printf("%lld %d %s\n", get_timestamp() - philo->start_time, philo->id, s);
	if (philo->is_dead == false)
		sem_post(data->print);
}