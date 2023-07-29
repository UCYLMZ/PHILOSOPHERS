/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick_starter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uyilmaz <uyilmaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 17:06:20 by uyilmaz           #+#    #+#             */
/*   Updated: 2023/07/30 01:21:54 by uyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	control_over(t_table *table)
{
	int	i;

	pthread_mutex_lock(&table->control_lock);
	i = -1;
	while (++i < table->rules->n_p)
	{
		if (table->full_flag)
			return (0);
		else if (table->dead_flag)
		{
			printer(table->philos[i], 4);
			pthread_mutex_unlock(&table->control_lock);
			return (0);
		}
	}
	pthread_mutex_unlock(&table->control_lock);
	return (1);
}

void	*routine(void *philo_void)
{
	int				check;
	long long		local_time;
	t_philosopher	*philo;

	philo = philo_void;
	while (control_over(philo->table))
	{
		eating(philo);
		if (!control_over(philo->table))
			return (NULL);
		sleeping(philo);
		if (!control_over(philo->table))
			return (NULL);
		printer(philo, 3);
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
