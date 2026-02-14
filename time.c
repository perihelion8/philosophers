/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 time.c												:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: abazzoun <abazzoun@student.42beirut.com>	+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2026/02/11 14:49:41 by abazzoun		   #+#	  #+#			  */
/*	 Updated: 2026/02/11 14:50:53 by abazzoun		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <unistd.h>
#include <stddef.h>
#include <sys/time.h>

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long milliseconds)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(500);
}
