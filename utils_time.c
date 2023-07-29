/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uyilmaz <uyilmaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 03:10:54 by uyilmaz           #+#    #+#             */
/*   Updated: 2023/07/30 01:18:22 by uyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	get_time(void)
{
	struct timeval	current_time;
	long long		time;

	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void	bedtime(int time, t_philosopher *philo)
{
	long long	localtime;

	localtime = get_time();
	while (loop_control(philo))
	{
		if (get_time() >= localtime + time)
			break ;
		usleep(100);
	}
}
