/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 13:57:23 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/05 17:35:53 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>

static int	is_arg_numeric(char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

int	ft_positive_atoi(char *nptr)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		i++;
	if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = (res * 10) + (nptr[i] - '0');
		i++;
	}
	return (res);
}

int	*parse_args(char **av)
{
	int	*tab;
	int	i;

	i = 1;
	while (av[i])
	{
		if (is_arg_numeric(av[i]))
			return (NULL);
		i++;
	}
	tab = malloc(sizeof(*tab) * (i - 1));
	i = 0;
	while (av[i + 1])
	{
		tab[i] = ft_positive_atoi(av[i + 1]);
		if (tab[i] == 0)
			return (free(tab), NULL);
		i++;
	}
	return (tab);
}
