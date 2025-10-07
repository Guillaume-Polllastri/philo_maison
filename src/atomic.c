/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atomic.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 22:53:15 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/07 23:09:20 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_game_running(t_data *data)
{
	int	death_flag;

	pthread_mutex_lock(&data->death_flag_lock);
	death_flag = data->death_flag;
	pthread_mutex_unlock(&data->death_flag_lock);
	return (death_flag == 0);
}
