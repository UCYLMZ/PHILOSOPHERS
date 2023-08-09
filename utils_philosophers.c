/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philosophers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uyilmaz <uyilmaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 19:22:18 by uyilmaz           #+#    #+#             */
/*   Updated: 2023/08/08 19:44:29 by uyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_mutexes(t_table *table)
{
	int	i;

	table->mutexes = malloc(sizeof(pthread_mutex_t) * table->rules->n_p);
	if (!table->mutexes)
		return (2);
	i = -1;
	while (++i < table->rules->n_p)
		pthread_mutex_init(&(table->mutexes[i]), NULL);
	pthread_mutex_init(&table->eat_lock, NULL);
	pthread_mutex_init(&table->sleep_lock, NULL);
	pthread_mutex_init(&table->die_lock, NULL);
	pthread_mutex_init(&table->flag_lock, NULL);
	pthread_mutex_init(&table->time_mutex, NULL);
	pthread_mutex_init(&table->print_mutex, NULL);
	return (0);
}

void	fill_philos(t_table *table, int i)
{
	table->philos[i]->table = table;
	table->philos[i]->last_meal = get_time();
	table->philos[i]->philo_id = i + 1;
	table->philos[i]->eaten = 0;
	table->philos[i]->philo = table->threads[i];
	if (i == 0)
	{
		table->philos[0]->right = &table->mutexes[0];
		table->philos[0]->left = &table->mutexes[table->rules->n_p - 1];
	}
	else
	{
		table->philos[i]->right = &table->mutexes[i];
		table->philos[i]->left = &table->mutexes[i - 1];
	}
}

void	init_philos(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->rules->n_p)
		fill_philos(table, i);
	table->time = get_time();
	i = -1;
	while (++i < table->rules->n_p)
	{
		pthread_create(&table->philos[i]->philo, 
			NULL, &routine, table->philos[i]);
		usleep(100);
	}
	while (1)
	{
		if (flag_control(table))
			break ;
	}
	i = -1;
	while (++i < table->rules->n_p)
		pthread_join(table->philos[i]->philo, NULL);
	i = -1;
	while (++i < table->rules->n_p)
		pthread_mutex_destroy(&(table->mutexes[i]));
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
