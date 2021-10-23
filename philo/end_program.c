/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsinistr <lsinistr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 18:07:33 by lsinistr          #+#    #+#             */
/*   Updated: 2021/10/21 13:42:47 by lsinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	end_program(t_condition *condition)
{
	int	i;

	while (condition->is_dead != 1 && condition->all_philo_eat_enough_time
		!= condition->number_of_philosophers)
		;
	i = -1;
	while (++i < condition->number_of_philosophers)
		pthread_mutex_destroy(&(condition->forks[i]));
	pthread_mutex_destroy(&(condition->message));
}
