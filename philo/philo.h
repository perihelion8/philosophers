/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abazzoun <abazzoun@student.42beirut.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 08:41:01 by abazzoun          #+#    #+#             */
/*   Updated: 2026/02/16 13:37:40 by abazzoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "rules.h"	

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	long			last_meal_time;
	int				meals_eaten;
	t_rules			*rules;
}	t_philo;

t_philo	*philos_create(t_rules *rules);
void	philos_destroy(t_philo *philos);
void	philos_join(t_philo *philos);
void	*philo_routine(void *arg);
void	philo_print(t_philo *philo, const char *str);

#endif
