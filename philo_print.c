/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 philo_print.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: abazzoun <abazzoun@student.42beirut.com>	+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2026/02/11 17:12:10 by abazzoun		   #+#	  #+#			  */
/*	 Updated: 2026/02/11 17:19:53 by abazzoun		  ###	########.fr		  */
/*																			  */
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
