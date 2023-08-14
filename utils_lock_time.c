/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lock_time.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uyilmaz <uyilmaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 13:56:00 by uyilmaz           #+#    #+#             */
/*   Updated: 2023/08/14 13:06:24 by uyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eating_lock(t_philosopher *philo)
{
	pthread_mutex_lock(philo->left);
	printer(philo, "has taken a fork");
	pthread_mutex_lock(philo->right);
	printer(philo, "has taken a fork");
}

void	eating_unlock(t_philosopher *philo)
{
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
}

int	printer(t_philosopher *philo, char *status)
{
	int static	written = 0;

	pthread_mutex_lock(&philo->table->print_mutex);
	if (!written)
	{
		if (status[0] != 'd')
		{
			pthread_mutex_lock(&philo->table->time_mutex);
			printf("%lld philosopher%d %s\n", get_time()
				- philo->table->time, philo->philo_id, status);
			pthread_mutex_unlock(&philo->table->time_mutex);
		}
		else
		{
			written = 1;
			pthread_mutex_lock(&philo->table->time_mutex);
			printf("%lld philosopher%d died\n", get_time()
				- philo->table->time, philo->philo_id);
			pthread_mutex_unlock(&philo->table->time_mutex);
		}
		pthread_mutex_unlock(&philo->table->print_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->table->print_mutex);
	return (1);
}

long long	get_time(void)
{
	struct timeval	current_time;
	long long		time;

	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void	pass_time(int time, t_philosopher *philo)
{
	long long	localtime;

	localtime = get_time();
	while (!flag_control(philo->table) && is_it_alive(philo))
	{
		if (get_time() >= localtime + time)
			break ;
		usleep(100);
	}
}
