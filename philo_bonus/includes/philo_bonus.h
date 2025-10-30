/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 15:56:11 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/30 10:48:19 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# define STR_MAX_INT "2147483647"
# define STR_MIN_INT "2147483648"

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

typedef struct s_data
{
	int			nb_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			nb_meals;
	sem_t		*forks;
	sem_t		*print;
}				t_data;

typedef struct s_philo
{
	int			id;
	int			nb_meals;
	long long	last_meal_time;
	long long	start_time;
	pid_t		pid;
	pthread_t	death;
	bool		is_dead;
	t_data		*data;
	pthread_t	reaper;
}				t_philo;

// atomic.c
void			print_philo_status(t_philo *philo, t_data *data, char *s);

// children.c
int				spawn_children(t_philo *philo, t_data *data);
void			wait_children(t_philo *philo, t_data *data);

// data_init.c
int				init_data(t_data *data, int *tab, int tab_len);

// death.c
void			*death_handler(void *arg);
void			kill_everyone(t_philo *philo, int index);

// parse.c
int				*parse_args(char **av);

// philo.c
void			routine_philos(t_philo *philo, t_data *data);
int				deploy_philos(t_data *data);

// semaphore.c
void			init_semaphore(t_data *data);
void			close_semaphore(t_data *data);

// the_order.c
int				get_order(int id, int nb_philos);
long long		get_time_to_think(t_philo *philo, t_data *data,
					bool is_starting);
// utils.c
long long		get_timestamp(void);
int				ft_strlen(char *s);
int				ft_strncmp(const char *s1, const char *s2, size_t n);

#endif