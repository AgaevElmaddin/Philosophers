/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsinistr <lsinistr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 17:13:25 by lsinistr          #+#    #+#             */
/*   Updated: 2021/10/20 17:13:26 by lsinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_time_meal(t_philo *philo)
{
	struct timeval	current_time;

	gettimeofday(&(current_time), NULL);
	return ((current_time.tv_sec - philo->last_time_lunch.tv_sec) * 1000
		+ (current_time.tv_usec - philo->last_time_lunch.tv_usec) / 1000);
}

void	*waiter_routine(void *sub_philo)
{
	t_condition	*condition;
	t_philo		*philo;

	philo = (t_philo *)sub_philo;
	condition = philo->condition;
	while (1)
	{
		usleep(150);
		if (check_time_meal(philo) >= condition->time_to_die)
		{
			sem_wait(condition->message);
			printf ("%ld %d died\n", calculate_time(condition),
				philo->index + 1);
			condition->is_dead = 1;
			exit(1);
		}
	}
	return (NULL);
}
