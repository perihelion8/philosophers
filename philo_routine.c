/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:23:30 by abazzoun          #+#    #+#             */
/*   Updated: 2026/02/14 08:40:48 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "time.h"
#include <unistd.h>

static void	pick_up_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->fork_l);
		pthread_mutex_lock(philo->fork_r);
	}
	else
	{
		pthread_mutex_lock(philo->fork_r);
		pthread_mutex_lock(philo->fork_l);
	}
}

static void	put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
}

static void	eat(t_philo *philo)
{
	long	current_time;

	philo_print(philo, "is eating");
	pthread_mutex_lock(&philo->rules->state_mutex);
	current_time = get_time();
	philo->last_meal_time = current_time;
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->rules->state_mutex);
	ft_usleep(philo->rules->time_to_eat);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->rules->number_of_philos == 1)
	{
		philo_print(philo, "is thinking");
		ft_usleep(philo->rules->time_to_die);
		return (NULL);
	}
	while (!simulation_ended(philo))
	{
		philo_print(philo, "is thinking");
		pick_up_forks(philo);
		eat(philo);
		put_down_forks(philo);
		philo_print(philo, "is sleeping");
		ft_usleep(philo->rules->time_to_sleep);
	}
	return (NULL);
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
