/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 13:32:22 by abazzoun          #+#    #+#             */
/*   Updated: 2026/02/16 13:33:20 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "philo.h"

int	simulation_setup(t_rules *rules, t_philo **philos, int argc, char **argv)
{
	if (!rules_init(rules, argc, argv))
		return (0);
	*philos = philos_create(rules);
	if (!(*philos))
	{
		free(rules->forks);
		return (0);
	}
	return (1);
}

int	simulation_ended(t_philo *philo)
{
	int	ended;

	pthread_mutex_lock(&philo->rules->state_mutex);
	ended = philo->rules->simulation_end;
	pthread_mutex_unlock(&philo->rules->state_mutex);
	return (ended);
}
