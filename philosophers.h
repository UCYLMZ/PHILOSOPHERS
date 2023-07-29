/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uyilmaz <uyilmaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 16:51:17 by uyilmaz           #+#    #+#             */
/*   Updated: 2023/07/30 01:18:36 by uyilmaz          ###   ########.fr       */
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
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	control_lock;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	sleep_mutex;
	pthread_mutex_t	time_mutex;
	pthread_mutex_t	loop_mutex;
}	t_table;

int			is_string_digit(char *str);
int			ft_atoi(const char *str);
int			kick_starter(t_table *table);
long long	get_time(void);
void		bedtime(int time, t_philosopher *philo);
int			create_mutexes(t_table *table);
void		init_philos(t_table *table);
void		*routine(void *table_void);
void		eating(t_philosopher *philo);
void		sleeping(t_philosopher *philo);
void		printer(t_philosopher *philo, int print_flag);
int			loop_control(t_philosopher *philo);
#endif