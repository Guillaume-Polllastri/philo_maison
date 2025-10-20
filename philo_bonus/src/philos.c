/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:59:53 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/20 17:03:45 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

static void	init_semaphore(t_data *data)
{
	data->forks = sem_open("/forks", O_CREAT | O_EXCL, 0644, data->nb_philos);
	data->print = sem_open("/print", O_CREAT | O_EXCL, 0644, 1);
	data->death = sem_open("/death", O_CREAT | O_EXCL, 0644, 0);
}

int deploy_philos(t_data *data)
{
	init_semaphore(data);
}
