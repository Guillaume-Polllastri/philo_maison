/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 20:48:21 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/29 13:27:21 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	init_semaphore(t_data *data)
{
	sem_unlink("/forks");
	sem_unlink("/print");
	data->forks = sem_open("/forks", O_CREAT | O_EXCL, 0644, data->nb_philos);
	data->print = sem_open("/print", O_CREAT | O_EXCL, 0644, 1);
}

void	close_semaphore(t_data *data)
{
	sem_close(data->forks);
	sem_close(data->print);
}
