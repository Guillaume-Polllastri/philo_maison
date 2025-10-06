/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 11:34:00 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/06 11:42:36 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

void    destroy_fork_mutex(pthread_mutex_t	*forks, int nb_initialized)
{
    int i;

    i = 0;
    while (i < nb_initialized)
    {
        pthread_mutex_destroy(&forks[i]);
        i++;
    }
    free(forks);
}
