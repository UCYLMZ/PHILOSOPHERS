/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uyilmaz <uyilmaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:56:00 by uyilmaz           #+#    #+#             */
/*   Updated: 2023/08/02 18:53:39 by uyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*eating_unlocker(t_philosopher *philo)
{
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
	return (NULL);
}

void	eating_locker(t_philosopher *philo)
{
	pthread_mutex_lock(philo->left);
	printer(philo, "has taken a fork");
	pthread_mutex_lock(philo->right);
	printer(philo, "has taken a fork");
}
