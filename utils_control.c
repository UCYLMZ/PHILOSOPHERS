/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uyilmaz <uyilmaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 18:58:11 by uyilmaz           #+#    #+#             */
/*   Updated: 2023/08/02 19:06:53 by uyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	loop_control(t_table *table)
{
	pthread_mutex_lock(&table->table_mutex);
	if (table->dead_flag || table->full_flag)
	{
		pthread_mutex_unlock(&table->table_mutex);
		return (1);
	}
	pthread_mutex_unlock(&table->table_mutex);
	return (0);
}
