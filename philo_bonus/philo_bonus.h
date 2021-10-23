/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsinistr <lsinistr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 17:13:41 by lsinistr          #+#    #+#             */
/*   Updated: 2021/10/20 18:14:07 by lsinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <semaphore.h>

typedef struct s_condition
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	sem_t			*forks;
	struct timeval	time_start;
	sem_t			*message;
	int				is_dead;
	int				all_philo_eat_enough_time;
	int				status;
}				t_condition;

typedef struct s_philo
{
	int				index;
	pid_t			philo_process;
	pthread_t		waiter_thread;
	t_condition		*condition;
	struct timeval	last_time_lunch;
	int				quantity_eat;

}				t_philo;

int		ft_atoi(const char *str);
long	calculate_time(t_condition *condition);
void	ft_usleep(int waiting_time, t_condition *condition);
void	*waiter_routine(void *sub_philo);
void	print_message(char *message, t_condition *condition, t_philo *philo);
void	error_message(char *message);
void	end_program_bonus(t_condition *condition, t_philo *philo);

#endif