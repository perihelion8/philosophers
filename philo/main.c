/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 21:48:19 by abazzoun          #+#    #+#             */
/*   Updated: 2026/02/18 13:41:44 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "simulation.h"
#include "monitor.h"

static int	is_number(const char *str)
{
	int	i;

	if (!str || !str[0] || str[0] == '-')
		return (0);
	i = 0;
	if (str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	in_range(const char *str)
{
	long	num;
	int		sign;
	int		i;

	num = 0;
	sign = 1;
	i = 0;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		if (sign * num > 2147483647 || sign * num < -2147483648)
			return (0);
		i++;
	}
	return (1);
}

static int	is_valid(const char *arg)
{
	if (!is_number(arg))
		return (0);
	if (!in_range(arg))
		return (0);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_rules		rules;
	t_philo		*philos;
	pthread_t	monitor;
	int			i;

	if (argc < 5 || argc > 6)
		return (1);
	i = 1;
	while (i < argc)
	{
		if (!is_valid(argv[i]))
			return (1);
		i++;
	}
	if (!simulation_setup(&rules, &philos, argc, argv))
		return (1);
	pthread_create(&monitor, NULL, monitor_routine, philos);
	philos_join(philos);
	pthread_join(monitor, NULL);
	philos_destroy(philos);
	return (0);
}
