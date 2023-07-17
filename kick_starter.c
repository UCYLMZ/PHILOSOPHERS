/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick_starter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uyilmaz <uyilmaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 10:55:55 by uyilmaz           #+#    #+#             */
/*   Updated: 2023/07/17 16:55:26 by uyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *philosopher_void)
{
	t_philosopher	*philo;

	philo = philosopher_void;
	printf("philosopher%d has created.\n", philo->philo_id);
	pthread_mutex_lock(&philo->left);
	pthread_mutex_lock(&philo->right);
	printf("philosopher%d is here!\n", philo->philo_id);
	pthread_mutex_unlock(&philo->left);
	pthread_mutex_unlock(&philo->right);
	printf("philosopher%d is out!\n", philo->philo_id);
	return (NULL);
}

void	mutex_initializer(t_table *table)
{
	int	i;

	table->mutexes = malloc(sizeof(pthread_mutex_t)
			* (table->rules->number_of_philosophers));
	if (!(table->mutexes))
		exit(2);
	i = -1;
	while (++i < table->rules->number_of_philosophers)
		pthread_mutex_init(&((table->mutexes)[i]), NULL);
}

void	philosophers_initializer(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->rules->number_of_philosophers)
	{
		((table->philosophers)[i])->philo_id = i + 1;
		if (i == 0)
		{
			(table->philosophers)[i]->left
				= table->mutexes[table->rules->number_of_philosophers - 1];
			(table->philosophers)[i]->right = table->mutexes[0];
		}
		else if (i == table->rules->number_of_philosophers - 1)
		{
			(table->philosophers)[i]->left
				= table->mutexes[table->rules->number_of_philosophers - 1];
			(table->philosophers)[i]->right = table->mutexes[0];
		}
		else
		{
			(table->philosophers)[i]->left
				= table->mutexes[table->rules->number_of_philosophers - 1];
			(table->philosophers)[i]->right = table->mutexes[i];
		}
	}
}

void	kick_starter(t_table *table)
{
	int	i;

	table->philosophers = malloc(sizeof(t_philosopher *)
			* (table->rules->number_of_philosophers) + 1);
	i = -1;
	while (++i < table->rules->number_of_philosophers)
		table->philosophers[i] = malloc(sizeof(t_philosopher));
	table->philosophers[i] = NULL;
	table->philosophers[0]->philo_id = 1;
	if (!(table->philosophers))
		exit(2);
	mutex_initializer(table);
	philosophers_initializer(table);
	i = -1;
	while (++i < table->rules->number_of_philosophers)
	{
		table->philo_index = i;
		pthread_create(&((table->philosophers)[i]->philo),
			NULL, &routine, table->philosophers[i]);
		usleep(10);
	}
}
