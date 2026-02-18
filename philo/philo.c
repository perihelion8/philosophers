/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 20:32:39 by abazzoun          #+#    #+#             */
/*   Updated: 2026/02/16 13:38:58 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "philo.h"
#include "rules.h"
#include "time.h"

t_philo	*philos_create(t_rules *rules)
{
	t_philo	*philos;
	int		i;

	philos = malloc(rules->number_of_philos * sizeof(*philos));
	if (!philos)
		return (NULL);
	i = 0;
	while (i < rules->number_of_philos)
	{
		philos[i].id = i + 1;
		philos[i].fork_l = rules->forks + i;
		philos[i].fork_r = rules->forks + ((i + rules->number_of_philos - 1)
				% rules->number_of_philos);
		philos[i].rules = rules;
		philos[i].last_meal_time = get_time();
		philos[i].meals_eaten = 0;
		pthread_create(&philos[i].thread, NULL, philo_routine, philos + i);
		i++;
	}
	return (philos);
}

void	philos_destroy(t_philo *philos)
{
	if (philos->rules->forks)
	{
		free(philos->rules->forks);
		philos->rules->forks = NULL;
	}
	free(philos);
}

void	philos_join(t_philo *philos)
{
	int	i;
	int	number_of_philos;

	number_of_philos = philos->rules->number_of_philos;
	i = 0;
	while (i < number_of_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}
