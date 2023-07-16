/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uyilmaz <uyilmaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 18:16:23 by uyilmaz           #+#    #+#             */
/*   Updated: 2023/07/16 20:48:03 by uyilmaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_arguments(int ac, char **arguments)
{
	int	i;
	int	flag;

	flag = 1;
	if (ac != 5 && ac != 6)
		flag *= 2;
	i = -1;
	while (arguments[++i])
	{
		if (!is_string_digit(arguments[i]))
			flag *= 3;
	}
	if (flag != 1)
	{
		if (flag % 2 == 0)
			printf("Error: Wrong argument count!\n");
		if (flag % 3 == 0)
			printf("Error: All arguments must be valid integer!\n");
		return (0);
	}
	return (1);
}

int	*check_values(int ac, char **arguments)
{
	int	i;
	int	*result;

	result = malloc(sizeof(int) * (ac));
	if (!result)
		exit (2);
	i = -1;
	while (++i < ac - 1) 
	{
		result[i] = ft_atoi(arguments[i]);
		if (result[i] <= 0)
		{
			printf("Error: Arguments must be bigger then zero!\n");
			exit (3);
		}
	}
	printf("#%d#\n", ac);
	result[i] = 0;
	return (result);
}

void	fill_the_rules(int ac, t_rules **ruller, int *values)
{
	(*ruller)->argument_count = ac - 1;
	(*ruller)->number_of_philosophers = values[0];
	(*ruller)->time_to_die = values[1];
	(*ruller)->time_to_eat = values[2];
	(*ruller)->time_to_sleep = values[3];
	if (ac == 6)
		(*ruller)->number_of_times_each_philosophers_must_eat = values[4];
	else
		(*ruller)->number_of_times_each_philosophers_must_eat = -1;
}

int	main(int ac, char **av)
{
	char	**arguments;
	int		*values;
	t_rules	*rules;

	arguments = &av[1];
	if (!check_arguments(ac, arguments))
		return (1);
	values = check_values(ac, arguments);
	rules = malloc(sizeof(t_rules));
	if (!rules)
		return (2);
	fill_the_rules(ac, &rules, values);
	printf("argument count:%d\n", rules->argument_count);
	printf("number of philosophers:%d\n", rules->number_of_philosophers);
	printf("time to die:%d\n", rules->time_to_die);
	printf("time to eat:%d\n", rules->time_to_eat);
	printf("time to sleep:%d\n", rules->time_to_sleep);
	printf("optional:%d\n", rules->number_of_times_each_philosophers_must_eat);
}
