/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uyilmaz <uyilmaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 16:51:17 by uyilmaz           #+#    #+#             */
/*   Updated: 2023/07/28 04:30:16 by uyilmaz          ###   ########.fr       */
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
	int				eaten;
	pthread_t		philo;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	struct s_table	*table;
	long long		last_meal;
}	t_philosopher;

typedef struct s_table
{
	t_rules			*rules;
	t_philosopher	**philos;
	pthread_t		*threads;
	pthread_mutex_t	*mutexes;
	long long		time;
	int				dead_flag;
	int				full_flag;
}	t_table;

int			is_string_digit(char *str);
int			ft_atoi(const char *str);
int			kick_starter(t_table *table);
long long	get_time(void);
int			create_mutexes(t_table *table);
void		init_philos(t_table *table);
void		*routine(void *table_void);
void		eating(t_philosopher *philo);
void		sleeping(t_philosopher *philo);
#endif