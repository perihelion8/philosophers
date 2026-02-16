/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 21:48:59 by abazzoun          #+#    #+#             */
/*   Updated: 2026/02/13 19:41:18 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "rules.h"
#include "time.h"

static pthread_mutex_t	*forks_make(int number_of_philos)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(number_of_philos * sizeof(*forks));
	if (!forks)
		return (NULL);
	i = 0;
	while (i < number_of_philos)
	{
		pthread_mutex_init(forks + i, NULL);
		i++;
	}
	return (forks);
}

static int	ft_atoi(const char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (sign * result);
}

int	rules_init(t_rules *rules, int argc, char **argv)
{
	rules->number_of_philos = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		rules->must_eat = -1;
	else
		rules->must_eat = ft_atoi(argv[5]);
	if (rules->number_of_philos <= 0 || rules->time_to_die <= 0
		|| rules->time_to_eat <= 0 || rules->time_to_sleep <= 0
		|| (argc == 6 && rules->must_eat <= 0))
	{
		printf("Error: positive values required\n");
		return (0);
	}
	rules->simulation_end = 0;
	rules->start_time = get_time();
	rules->forks = forks_make(rules->number_of_philos);
	if (!rules->forks)
		return (0);
	pthread_mutex_init(&rules->state_mutex, NULL);
	return (1);
}
