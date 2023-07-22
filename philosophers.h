/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uyilmaz <uyilmaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 16:51:17 by uyilmaz           #+#    #+#             */
/*   Updated: 2023/07/22 04:21:02 by uyilmaz          ###   ########.fr       */
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
	int	n_p;
	int	die;
	int	eat;
	int	sleep;
	int	must_eat;
	int	argument_count;
}	t_rules;

typedef struct s_philosopher
{
	int				philo_id;
	pthread_t		philo;
	pthread_mutex_t	left;
	pthread_mutex_t	right;
	struct s_table	*table;
}	t_philosopher;

typedef struct s_table
{
	t_rules			*rules;
	t_philosopher	**p_t;
	pthread_mutex_t	*mutexes;
	int				philo_index;
	long long		time;
}	t_table;

char		**ft_split(const char *s, char c);
int			is_string_digit(char *str);
int			ft_atoi(const char *str);
void		kick_starter(t_table *table);
long long	get_time(void);
#endif