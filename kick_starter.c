/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick_starter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uyilmaz <uyilmaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:06:20 by uyilmaz           #+#    #+#             */
/*   Updated: 2023/07/28 04:31:40 by uyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	control_over(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->rules->n_p)
	{
		if (table->philos[i]->eaten >= table->rules->must_eat)
			return (0);
		else if (table->philos[i]->last_meal + table->rules->die < get_time())
		{
			printf("%lld philosopher%d is died\n", get_time()
				- table->time, table->philos[i]->philo_id);
			return (0);
		}
	}
	return (1);
}

void	*routine(void *philo_void)
{
	int				check;
	t_philosopher	*philo;

	philo = philo_void;
	while (control_over(philo->table))
	{
		pthread_mutex_lock(philo->left);
		pthread_mutex_lock(philo->right);
		eating(philo);
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
		if (philo->table->dead_flag || philo->table->full_flag)
			return (NULL);
		printf("%lld philosopher%d is thinking\n", get_time()
			- philo->table->time, philo->philo_id);
	}
	return (NULL);
}

int	kick_starter(t_table *table)
{
	int	i;

	if (create_mutexes(table))
		return (2);
	table->philos = malloc(sizeof(t_philosopher *) * table->rules->n_p);
	table->threads = malloc(sizeof(pthread_t) * table->rules->n_p);
	i = -1;
	while (++i < table->rules->n_p)
	{
		table->philos[i] = malloc(sizeof(t_philosopher));
		if (!table->philos[i])
			return (2);
	}
	if (!table->philos || !table->threads)
		return (2);
	table->dead_flag = 0;
	table->full_flag = 0;
	init_philos(table);
	return (0);
}
