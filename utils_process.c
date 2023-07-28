/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uyilmaz <uyilmaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:25:55 by uyilmaz           #+#    #+#             */
/*   Updated: 2023/07/28 04:32:08 by uyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eating(t_philosopher *philo)
{
	long long	local_time;

	local_time = get_time() - philo->table->time;
	philo->eaten += 1;
	printf("%lld philosopher%d is eating\n", local_time, philo->philo_id);
	if (philo->last_meal + philo->table->rules->die < get_time())
	{
		printf("%lld philosopher%d is died\n", get_time()
			- philo->table->time, philo->philo_id);
		philo->table->dead_flag = 1;
	}
	philo->last_meal = get_time();
	while (get_time() < philo->table->time + philo->table->rules->eat)
		usleep(100);
	if (philo->eaten >= philo->table->rules->must_eat)
		philo->table->full_flag = 1;
}

void	sleeping(t_philosopher *philo)
{
	long long	local_time;

	local_time = get_time() - philo->table->time;
	printf("%lld philosopher%d is sleeping\n", local_time, philo->philo_id);
	if (philo->last_meal + philo->table->rules->die < get_time())
	{
		printf("%lld philosopher%d is died\n", get_time()
			- philo->table->time, philo->philo_id);
		philo->table->dead_flag = 1;
	}
	while (get_time() < philo->table->time + philo->table->rules->sleep)
		usleep(100);
	if (philo->last_meal + philo->table->rules->die < get_time())
	{
		printf("%lld philosopher%d is died sleeping\n", get_time()
			- philo->table->time, philo->philo_id);
		philo->table->dead_flag = 1;
	}
}
