/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:56:11 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/20 12:52:31 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# define STR_MAX_INT "2147483647"
# define STR_MIN_INT "2147483648"

# include <pthread.h>
# include <stdbool.h>

typedef struct s_data
{
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meals;
}					t_data;

int	    *parse_args(char **av);
int     ft_strlen(char *s);
int	    ft_strncmp(const char *s1, const char *s2, size_t n);
void	init_data(t_data *data, int *tab, int tab_len);

#endif 