/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uyilmaz <uyilmaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 16:51:17 by uyilmaz           #+#    #+#             */
/*   Updated: 2023/07/17 13:30:57 by uyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_rules
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosophers_must_eat;
	int	argument_count;
}	t_rules;

typedef struct s_philosopher
{
	int				philo_id;
	pthread_t		philo;
	pthread_mutex_t	left;
	pthread_mutex_t	right;
}	t_philosopher;

typedef struct s_table
{
	t_rules			*rules;
	pthread_t		*philos;
	t_philosopher	**philosophers;
	pthread_mutex_t	*mutexes;
	int				philo_index;
}	t_table;

char	**ft_split(const char *s, char c);
int		is_string_digit(char *str);
int		ft_atoi(const char *str);
void	kick_starter(t_table *table);
#endif