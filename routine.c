/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uyilmaz <uyilmaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:21:17 by uyilmaz           #+#    #+#             */
/*   Updated: 2023/08/13 04:07:30 by uyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	eating_control(t_philosopher *philo)
{
	if (philo->eaten == philo->table->rules->must_eat)
	{
		pthread_mutex_lock(&philo->eaten_lock);
		philo->full_flag = 1;
		pthread_mutex_unlock(&philo->eaten_lock);
		return (0);
	}
	eating_lock(philo);
	if (!is_it_alive(philo))
	{
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
		return (0);
	}
	return (1);
}

int	eating(t_philosopher *philo)
{
	int	eat;

	if (!eating_control(philo))
		return (0);
	printer(philo, "is eating");
	pthread_mutex_lock(&philo->table->eat_lock);
	eat = philo->table->rules->eat;
	pthread_mutex_unlock(&philo->table->eat_lock);
	pthread_mutex_lock(&philo->table->die_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->table->die_lock);
	pass_time(eat, philo);
	pthread_mutex_lock(&philo->eaten_lock);
	philo->eaten += 1;
	pthread_mutex_unlock(&philo->eaten_lock);
	eating_unlock(philo);
	return (1);
}

int	sleeping(t_philosopher *philo)
{
	int	sleep;

	if (philo->eaten == philo->table->rules->must_eat)
	{
		pthread_mutex_lock(&philo->eaten_lock);
		philo->full_flag = 1;
		pthread_mutex_unlock(&philo->eaten_lock);
		return (0);
	}
	if (!is_it_alive(philo))
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
