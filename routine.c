/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uyilmaz <uyilmaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:21:17 by uyilmaz           #+#    #+#             */
/*   Updated: 2023/08/09 13:07:32 by uyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	eating(t_philosopher *philo)
{
	int	eat;

	pthread_mutex_lock(philo->left);
	pthread_mutex_lock(philo->right);
	if (!is_it_alive(philo) || flag_control(philo->table))
	{
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
		return (0);
	}
	if (!is_it_alive(philo) || flag_control(philo->table))
	{
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
		return (0);
	}
	printer(philo, "is eating");
	pthread_mutex_lock(&philo->table->eat_lock);
	eat = philo->table->rules->eat;
	pthread_mutex_unlock(&philo->table->eat_lock);
	pass_time(eat, philo);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
	return (1);
}

int	sleeping(t_philosopher *philo)
{
	int	sleep;

	if (!is_it_alive(philo) || flag_control(philo->table))
		return (0);
	pthread_mutex_lock(&philo->table->sleep_lock);
	sleep = philo->table->rules->sleep;
	pthread_mutex_unlock(&philo->table->sleep_lock);
	printer(philo, "is sleeping");
	pass_time(sleep, philo);
	return (1);
}

void	*routine(void *philo_void)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)philo_void;
	while (!flag_control(philo->table))
	{
		if (!eating(philo))
			return (NULL);
		if (!sleeping(philo))
			return (NULL);
		printer(philo, "is thinking");
	}
	return (NULL);
}
