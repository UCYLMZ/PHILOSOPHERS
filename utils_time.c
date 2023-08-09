/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uyilmaz <uyilmaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 03:10:54 by uyilmaz           #+#    #+#             */
/*   Updated: 2023/08/09 12:58:05 by uyilmaz          ###   ########.fr       */
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

	localtime = get_time();
	while (!flag_control(philo->table) && is_it_alive(philo))
	{
		if (get_time() >= localtime + time)
			break ;
		usleep(100);
	}
}
