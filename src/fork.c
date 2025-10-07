/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 20:16:08 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/07 20:30:01 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

t_fork	*create_fork(void)
{
	t_fork	*fork;

	fork = malloc(sizeof(*fork));
	if (!fork)
		return (NULL);
	fork->owner = 0;
	pthread_mutex_init(&fork->mutex, NULL);
	return (fork);
}
