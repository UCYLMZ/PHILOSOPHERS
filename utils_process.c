/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uyilmaz <uyilmaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 21:25:55 by uyilmaz           #+#    #+#             */
/*   Updated: 2023/07/30 01:40:11 by uyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	loop_control(t_philosopher *philo)
{
	t_table	*table;

	pthread_mutex_lock(&philo->table->loop_mutex);
	table = philo->table;
	//printf("dead_flag: %d   full_flag: %d\n", table->dead_flag, table->full_flag);
	if (table->dead_flag == 1 || table->full_flag == 1)
	{
		pthread_mutex_unlock(&table->loop_mutex);
		return (0);
	}
	pthread_mutex_unlock(&table->loop_mutex);
	return (1);
}

void	printer(t_philosopher *philo, int print_flag)
{
	pthread_mutex_lock(&philo->table->print_mutex);
	if (print_flag == 0)
		printf("%lld philosopher%d has taken a fork\n", get_time()
			- philo->table->time, philo->philo_id);
	else if (print_flag == 1)
		printf("%lld philosopher%d is eating\n", get_time()
			- philo->table->time, philo->philo_id);
	else if (print_flag == 2)
		printf("%lld philosopher%d is sleeping\n", get_time()
			- philo->table->time, philo->philo_id);
	else if (print_flag == 3)
		printf("%lld philosopher%d is thinking\n", get_time()
			- philo->table->time, philo->philo_id);
	else if (print_flag == 4)
		printf("%lld philosopher%d died\n", get_time()
			- philo->table->time, philo->philo_id);
	pthread_mutex_unlock(&philo->table->print_mutex);
}

void	eating(t_philosopher *philo)
{
	long long	local_time;

	pthread_mutex_lock(philo->left);
	printer(philo, 0);
	pthread_mutex_lock(philo->right);
	printer(philo, 0);
	pthread_mutex_lock(&philo->table->eat_lock);
	philo->eaten += 1;
	philo->last_meal = get_time();
	if (philo->eaten >= philo->table->rules->must_eat
		&& philo->table->rules->must_eat > 0)
		philo->table->full_flag = 1;
	printer(philo, 1);
	if (philo->last_meal + philo->table->rules->die < get_time())
	{
		printer(philo, 4);
		printf("eating\n");
		philo->table->dead_flag = 1;
	}
	pthread_mutex_unlock(&philo->table->eat_lock);
	local_time = get_time();
	if (loop_control(philo))
		bedtime(philo->table->rules->eat, philo);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
}

void	sleeping(t_philosopher *philo)
{
	long long	local_time;

	pthread_mutex_lock(&philo->table->sleep_mutex);
	local_time = get_time();
	printer(philo, 2);
	if (philo->last_meal + philo->table->rules->die < get_time())
	{
		printer(philo, 4);
		printf("sleeping1\n");
		philo->table->dead_flag = 1;
	}
	bedtime(philo->table->rules->sleep, philo);
	printf("philo_id: %d dead_flag: %d\n", philo->philo_id, philo->table->dead_flag);
	if (philo->last_meal + philo->table->rules->die < get_time())
	{
		printer(philo, 4);
		printf("sleeping2\n");
		philo->table->dead_flag = 1;
	}
	pthread_mutex_unlock(&philo->table->sleep_mutex);
}
