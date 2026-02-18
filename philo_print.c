/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:32:33 by abazzoun          #+#    #+#             */
/*   Updated: 2026/02/18 13:32:34 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"
#include "time.h"

void	philo_print(t_philo *philo, const char *status)
{
	long	timestamp;

	pthread_mutex_lock(&philo->rules->state_mutex);
	if (philo->rules->simulation_end)
	{
		pthread_mutex_unlock(&philo->rules->state_mutex);
		return ;
	}
	timestamp = get_time() - philo->rules->start_time;
	printf("%ld %d %s\n", timestamp, philo->id, status);
	pthread_mutex_unlock(&philo->rules->state_mutex);
}
