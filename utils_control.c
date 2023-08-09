/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uyilmaz <uyilmaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:58:11 by uyilmaz           #+#    #+#             */
/*   Updated: 2023/08/09 12:56:30 by uyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	flag_control(t_table *table)
{
	pthread_mutex_lock(&table->flag_lock);
	if (table->dead_flag || table->full_flag)
	{
		pthread_mutex_unlock(&table->flag_lock);
		return (1);
	}
	pthread_mutex_unlock(&table->flag_lock);
	return (0);
}

int	set_flags(t_table *table, int flag)
{
	pthread_mutex_lock(&table->flag_lock);
	if (flag == 0)
		table->full_flag = 1;
	else
	{
		table->dead_flag = 1;
		printer(table->philos[flag], "died");
	}
	return (1);
}

int	is_it_alive(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->table->die_lock);
	if (philo->last_meal + philo->table->rules->die < get_time())
	{
		pthread_mutex_unlock(&philo->table->die_lock);
		return (!set_flags(philo->table, philo->philo_id));
	}
	pthread_mutex_unlock(&philo->table->die_lock);
	return (1);
}
