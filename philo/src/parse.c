/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 13:57:23 by gpollast          #+#    #+#             */
/*   Updated: 2025/10/29 13:17:13 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include <stdlib.h>
#include <unistd.h>

static int	is_arg_numeric(char *s)
{
	int	i;

	i = 0;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == ' ')
		i++;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

static int	check_int_value(char *str)
{
	char	*cmp;

	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			cmp = STR_MIN_INT;
		str++;
	}
	cmp = STR_MAX_INT;
	if (ft_strlen(str) == ft_strlen(cmp))
		return (ft_strncmp(cmp, str, ft_strlen(cmp)));
	else
		return (ft_strlen(cmp) - ft_strlen(str));
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
			return (write(2, "Error\nArguments must be an int\n", 36), NULL);
		if (check_int_value(av[i]) < 0)
			return (write(2, "Error\nArguments must be an int\n", 36), NULL);
		i++;
	}
	tab = malloc(sizeof(*tab) * (i - 1));
	i = 0;
	while (av[i + 1])
	{
		tab[i] = ft_positive_atoi(av[i + 1]);
		if (tab[i] == 0)
		{
			write(2, "Error\nArguments must be a positive non-nul value\n", 49);
			return (free(tab), NULL);
		}
		i++;
	}
	return (tab);
}
