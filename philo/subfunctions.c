/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subfunctions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsinistr <lsinistr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 17:10:10 by lsinistr          #+#    #+#             */
/*   Updated: 2021/10/20 18:07:15 by lsinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_atoi(const char *str)
{
	unsigned long	res;
	int				i;
	int				count_minus;

	count_minus = 1;
	res = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			count_minus = -1;
	while (str[i] >= '0' && str[i] <= '9')
		res = res * 10 + (str[i++] - '0');
	if (res > 9223372036854775807)
	{
		if (count_minus == 1)
			return (0);
		return (-1);
	}
	return (res * count_minus);
}

void	print_message(char *message, t_condition *condition, t_philo *philo)
{
	pthread_mutex_lock(&(condition->message));
	printf ("%ld %d %s\n", calculate_time(condition), philo->index + 1, message);
	pthread_mutex_unlock(&(condition->message));
}

long	calculate_time(t_condition *condition)
{
	struct timeval	current_time;

	gettimeofday(&(current_time), NULL);
	return ((current_time.tv_sec - condition->time_start.tv_sec) * 1000
		+ (current_time.tv_usec - condition->time_start.tv_usec) / 1000);
}

void	ft_usleep(int waiting_time, t_condition *condition)
{
	long	end_time;
	int		count;

	end_time = calculate_time(condition) + waiting_time;
	count = 200 + (condition->number_of_philosophers * 4);
	while (calculate_time(condition) < end_time)
		usleep(count);
}

void	error_message(char *message)
{
	printf("%s\n", message);
	exit (0);
}
