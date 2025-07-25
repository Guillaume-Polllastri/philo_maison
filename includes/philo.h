/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:41:40 by gpollast          #+#    #+#             */
/*   Updated: 2025/07/25 14:56:47 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

int	ft_atoi(char *nptr);
int	*parse_args(char **av);

typedef struct s_info
{
	int	x;
}	t_info;

typedef struct s_philo
{
	int	x;
}	t_philo;

#endif