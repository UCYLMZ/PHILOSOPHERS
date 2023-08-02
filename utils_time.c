/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uyilmaz <uyilmaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 03:10:54 by uyilmaz           #+#    #+#             */
/*   Updated: 2023/07/31 14:35:03 by uyilmaz          ###   ########.fr       */
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

void	pass_time(int time, t_philosopher *philo)
{
	long long	localtime;

	pthread_mutex_lock(&philo->table->time_mutex);
	localtime = get_time();
	pthread_mutex_unlock(&philo->table->time_mutex);
	while (control_over(philo->table))
	{
		if (get_time() >= localtime + time)
			break ;
		usleep(100);
	}
}
