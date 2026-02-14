/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 14:37:07 by abazzoun          #+#    #+#             */
/*   Updated: 2026/02/14 08:15:49 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
#include "philo.h"
#include "time.h"

int	check_all_ate(t_philo *philos)
{
	int	i;
	int	count;

	if (philos[0].rules->must_eat == -1)
		return (0);
	i = 0;
	count = 0;
	while (i < philos[0].rules->number_of_philos)
	{
		pthread_mutex_lock(&philos[0].rules->state_mutex);
		if (philos[i].meals_eaten >= philos[0].rules->must_eat)
			count++;
		pthread_mutex_unlock(&philos[0].rules->state_mutex);
		i++;
	}
	return (count == philos[0].rules->number_of_philos);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philos;
	int		i;
	long	time_diff;

	philos = arg;
	while (1)
	{
		i = 0;
		while (i < philos[0].rules->number_of_philos)
		{
			pthread_mutex_lock(&philos[i].rules->state_mutex);
			time_diff = get_time() - philos[i].last_meal_time;
			if (time_diff > philos[i].rules->time_to_die)
			{
				pthread_mutex_unlock(&philos[0].rules->state_mutex);
				philo_print(&philos[i], "died");
				pthread_mutex_lock(&philos[0].rules->state_mutex);
				philos[0].rules->simulation_end = 1;
				pthread_mutex_unlock(&philos[0].rules->state_mutex);
				return (NULL);
			}
			pthread_mutex_unlock(&philos[i].rules->state_mutex);
			i++;
		}
		if (check_all_ate(philos))
		{
			pthread_mutex_lock(&philos[0].rules->state_mutex);
			philos[0].rules->simulation_end = 1;
			pthread_mutex_unlock(&philos[0].rules->state_mutex);
			return (NULL);
		}
		ft_usleep(5);
	}
	return (NULL);
}
