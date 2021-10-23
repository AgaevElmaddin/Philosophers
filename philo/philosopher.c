/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsinistr <lsinistr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 17:09:13 by lsinistr          #+#    #+#             */
/*   Updated: 2021/10/21 13:38:37 by lsinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	parser(int argc, char **argv, t_condition *condition)
{
	if (argc != 5 && argc != 6)
	{
		printf("Think better!\n");
		return (0);
	}
	condition->number_of_philosophers = ft_atoi(argv[1]);
	condition->time_to_die = ft_atoi(argv[2]);
	condition->time_to_eat = ft_atoi(argv[3]);
	condition->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		condition->number_of_times_each_philosopher_must_eat = -1;
	else
		condition->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	return (1);
}

int	take_forks(t_philo *philo, t_condition *condition)
{
	int	i;

	i = -1;
	gettimeofday(&(condition->time_start), NULL);
	while (++i < condition->number_of_philosophers)
	{
		if (pthread_mutex_init(&(condition->forks[i]), NULL) != 0)
			error_message("Can't initialize mutex");
		philo[i].index = i;
		philo[i].right_fork = i;
		philo[i].left_fork = (i + 1) % condition->number_of_philosophers;
		philo[i].condition = condition;
		philo[i].last_time_lunch = condition->time_start;
		philo[i].quantity_eat = 0;
	}
	condition->is_dead = 0;
	condition->all_philo_eat_enough_time = 0;
	if (pthread_mutex_init(&(condition->message), NULL) != 0)
		error_message("Can't initialize mutex");
	if (pthread_mutex_init(&(condition->is_ate), NULL) != 0)
		error_message("Can't initialize mutex");
	return (1);
}

void	lunch_time(t_condition *condition, t_philo *philo)
{
	pthread_mutex_lock(&(condition->forks[philo->right_fork]));
	print_message("has taken a fork\n", condition, philo);
	pthread_mutex_lock(&(condition->forks[philo->left_fork]));
	print_message("has taken a fork\n", condition, philo);
	gettimeofday(&(philo->last_time_lunch), NULL);
	print_message("is eating\n", condition, philo);
	philo->quantity_eat++;
	if (philo->quantity_eat
		== condition->number_of_times_each_philosopher_must_eat)
	{
		pthread_mutex_lock(&(condition->is_ate));
		condition->all_philo_eat_enough_time++;
		pthread_mutex_unlock(&(condition->is_ate));
	}
	ft_usleep(condition->time_to_eat, condition);
	pthread_mutex_unlock(&(condition->forks[philo->right_fork]));
	pthread_mutex_unlock(&(condition->forks[philo->left_fork]));
}

void	*philo_routine(void *sub_philo)
{
	t_philo		*philo;
	t_condition	*condition;

	philo = (t_philo *)sub_philo;
	condition = philo->condition;
	if (philo->index % 2 == 0)
		usleep(150);
	while (1)
	{
		lunch_time(condition, philo);
		print_message("is sleeping\n", condition, philo);
		ft_usleep(condition->time_to_sleep, condition);
		print_message("is thinking\n", condition, philo);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_condition	condition;
	t_philo		philo[200];
	int			i;

	i = -1;
	if (parser(argc, argv, &condition) == 0
		|| take_forks(philo, &condition) == 0)
		return (0);
	while (++i < condition.number_of_philosophers)
	{
		if (pthread_create(&(philo[i].philo_thread),
				NULL, philo_routine, (void *)&(philo[i])) != 0)
			error_message("Can't create thread!");
		if (pthread_create(&(philo[i].waiter_thread),
				NULL, waiter_routine, (void *)(&philo[i])) != 0)
			error_message("Can't create thread!");
		pthread_detach(philo[i].philo_thread);
		pthread_detach(philo[i].waiter_thread);
	}
	end_program(&condition);
	return (0);
}
