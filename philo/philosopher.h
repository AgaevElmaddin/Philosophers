/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsinistr <lsinistr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 17:09:42 by lsinistr          #+#    #+#             */
/*   Updated: 2021/10/20 18:07:22 by lsinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>

typedef struct s_condition
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	pthread_mutex_t	forks[200];
	struct timeval	time_start;
	pthread_mutex_t	message;
	pthread_mutex_t	is_ate;
	int				is_dead;
	int				all_philo_eat_enough_time;
}				t_condition;

typedef struct s_philo
{
	int				left_fork;
	int				right_fork;
	int				index;
	pthread_t		philo_thread;
	pthread_t		waiter_thread;
	t_condition		*condition;
	struct timeval	last_time_lunch;
	int				quantity_eat;

}				t_philo;

int		ft_atoi(const char *str);
long	calculate_time(t_condition *condition);
void	print_message(char *message, t_condition *condition, t_philo *philo);
void	ft_usleep(int waiting_time, t_condition *condition);
void	*waiter_routine(void *sub_philo);
void	error_message(char *message);
void	end_program(t_condition *condition);

#endif