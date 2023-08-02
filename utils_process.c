/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uyilmaz <uyilmaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:25:55 by uyilmaz           #+#    #+#             */
/*   Updated: 2023/08/02 12:33:31 by uyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	control_over(t_table *table)
{
	pthread_mutex_lock(&table->control_lock);
	if (table->dead_flag || table->full_flag)
	{
		pthread_mutex_unlock(&table->control_lock);
		return (0);
	}
	pthread_mutex_unlock(&table->control_lock);
	return (1);
}

void	set_flag(t_table *table)
{
	
}

int	printer(t_philosopher *philo, char *status)
{
	int static	written = 0;

	pthread_mutex_lock(&philo->table->print_mutex);
	if (!written)
	{
		if (status[0] != 'd')
			printf("%lld philosopher%d %s\n", get_time()
				- philo->table->time, philo->philo_id, status);
		else
		{
			written = 1;
			printf("%lld philosopher%d died\n", get_time()
				- philo->table->time, philo->philo_id);
		}
		pthread_mutex_unlock(&philo->table->print_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->table->print_mutex);
	return (1);
}
