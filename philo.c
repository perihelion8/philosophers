/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 20:32:39 by abazzoun          #+#    #+#             */
/*   Updated: 2026/02/11 17:39:14 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo.h"
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

t_philo	*philos_create(t_rules *rules)
{
	t_philo			*philos;
	pthread_mutex_t	*forks;
	int				i;

	forks = forks_make(rules->number_of_philos);
	if (!forks)
		return (NULL);
	rules->forks = forks;
	philos = malloc(rules->number_of_philos * sizeof(*philos));
	if (!philos)
	{
		free(forks);
		return (NULL);
	}
	i = 0;
	while (i < rules->number_of_philos)
	{
		philos[i].id = i + 1;
		philos[i].fork_l = forks + i;
		philos[i].fork_r = forks + ((i + rules->number_of_philos - 1)
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

int	simulation_ended(t_philo *philo)
{
	int	ended;

	pthread_mutex_lock(&philo->rules->state_mutex);
	ended = philo->rules->simulation_end;
	pthread_mutex_unlock(&philo->rules->state_mutex);
	return (ended);
}
