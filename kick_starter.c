/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick_starter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uyilmaz <uyilmaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 10:55:55 by uyilmaz           #+#    #+#             */
/*   Updated: 2023/07/22 04:23:50 by uyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *philosopher_void)
{
	t_philosopher	*philo;

	philo = philosopher_void;
	printf("philosopher%d has created.\n", philo->philo_id);
	if ((philo->philo_id) % 2 == 0)
		usleep(100);
	pthread_mutex_lock(&philo->left);
	printf("%lld philosopher%d has taken a fork!\n", get_time()
		- philo->table->time, philo->philo_id);
	pthread_mutex_lock(&philo->right);
	printf("%lld philosopher%d has taken a fork!\n", get_time()
		- philo->table->time, philo->philo_id);
	eating(philo);
	pthread_mutex_unlock(&philo->left);
	pthread_mutex_unlock(&philo->right);
	return (NULL);
}

void	mutex_initializer(t_table *table)
{
	int	i;

	table->mutexes = malloc(sizeof(pthread_mutex_t)
			* (table->rules->n_p));
	if (!(table->mutexes))
		exit(2);
	i = -1;
	while (++i < table->rules->n_p)
		pthread_mutex_init(&((table->mutexes)[i]), NULL);
}

void	philosophers_initializer(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->rules->n_p)
	{
		((table->p_t)[i])->philo_id = i + 1;
		table->p_t[i]->table = table;
		if (i == 0)
		{
			(table->p_t)[i]->left = table->mutexes[table->rules->n_p - 1];
			(table->p_t)[i]->right = table->mutexes[0];
		}
		else if (i == table->rules->n_p - 1)
		{
			(table->p_t)[i]->left = table->mutexes[table->rules->n_p - 1];
			(table->p_t)[i]->right = table->mutexes[0];
		}
		else
		{
			(table->p_t)[i]->left = table->mutexes[table->rules->n_p - 1];
			(table->p_t)[i]->right = table->mutexes[i];
		}
	}
}

void	kick_starter(t_table *table)
{
	int				i;

	table->p_t = malloc(sizeof(t_philosopher *)
			* (table->rules->n_p) + 1);
	i = -1;
	while (++i < table->rules->n_p)
		table->p_t[i] = malloc(sizeof(t_philosopher));
	table->p_t[i] = NULL;
	table->p_t[0]->philo_id = 1;
	if (!(table->p_t))
		exit(2);
	mutex_initializer(table);
	philosophers_initializer(table);
	i = -1;
	table->time = get_time();
	while (++i < table->rules->n_p)
	{
		table->philo_index = i;
		pthread_create(&((table->p_t)[i]->philo),
			NULL, &routine, table->p_t[i]);
	}
}
