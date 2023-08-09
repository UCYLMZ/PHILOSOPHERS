/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lock.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uyilmaz <uyilmaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:56:00 by uyilmaz           #+#    #+#             */
/*   Updated: 2023/08/09 12:51:13 by uyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	printer(t_philosopher *philo, char *status)
{
	int static	written = 0;

	pthread_mutex_lock(&philo->table->print_mutex);
	if (!written)
	{
		if (status[0] != 'd')
		{
			pthread_mutex_lock(&philo->table->time_mutex);
			printf("%lld philosopher%d %s\n", get_time()
				- philo->table->time, philo->philo_id, status);
			pthread_mutex_unlock(&philo->table->time_mutex);
		}
		else
		{
			written = 1;
			pthread_mutex_lock(&philo->table->time_mutex);
			printf("%lld philosopher%d died\n", get_time()
				- philo->table->time, philo->philo_id);
			pthread_mutex_unlock(&philo->table->time_mutex);
		}
		pthread_mutex_unlock(&philo->table->print_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->table->print_mutex);
	return (1);
}