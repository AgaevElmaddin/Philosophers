/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsinistr <lsinistr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 17:13:44 by lsinistr          #+#    #+#             */
/*   Updated: 2021/10/20 18:14:27 by lsinistr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

	sem_unlink("forks");
	sem_unlink("message");
	i = -1;
	gettimeofday(&(condition->time_start), NULL);
	while (++i < condition->number_of_philosophers)
	{
		condition->forks = sem_open("forks", O_CREAT, S_IRWXU,
				condition->number_of_philosophers);
		if (condition->forks == SEM_FAILED)
			error_message("Can't initialize semaphore");
		philo[i].index = i;
		philo[i].condition = condition;
		philo[i].last_time_lunch = condition->time_start;
		philo[i].quantity_eat = 0;
	}
	condition->is_dead = 0;
	condition->all_philo_eat_enough_time = 0;
	condition->message = sem_open("message", O_CREAT, S_IRWXU, 1);
	if (condition->message == SEM_FAILED)
		error_message("Can't initialize semaphore");
	return (1);
}

void	lunch_time(t_condition *condition, t_philo *philo)
{
	sem_wait(condition->forks);
	print_message("has taken a fork\n", condition, philo);
	sem_wait(condition->forks);
	print_message("has taken a fork\n", condition, philo);
	gettimeofday(&(philo->last_time_lunch), NULL);
	print_message("is eating\n", condition, philo);
	philo->quantity_eat++;
	ft_usleep(condition->time_to_eat, condition);
	sem_post(condition->forks);
	sem_post(condition->forks);
	if (philo->quantity_eat
		== condition->number_of_times_each_philosopher_must_eat)
		exit(0);
}

void	philo_routine(t_philo *philo, t_condition *condition)
{
	if (pthread_create(&(philo->waiter_thread),
			NULL, waiter_routine, (void *)(philo)) != 0)
		error_message("Can't create thread!");
	pthread_detach(philo->waiter_thread);
	if (philo->index % 2 == 0)
		usleep(150);
	while (1)
	{
		lunch_time(condition, philo);
		print_message("is sleeping\n", condition, philo);
		ft_usleep(condition->time_to_sleep, condition);
		print_message("is thinking\n", condition, philo);
	}
}

int	main(int argc, char **argv)
{
	t_condition	condition;
	t_philo		philo[200];
	int			i;

	i = -1;
	if (parser(argc, argv, &condition) == 0)
		return (0);
	if (take_forks(philo, &condition) == 0)
		return (0);
	while (++i < condition.number_of_philosophers)
	{
		philo[i].philo_process = fork();
		if (philo[i].philo_process == -1)
			error_message("Can't create process");
		if (philo[i].philo_process == 0)
			philo_routine(&(philo[i]), &condition);
	}
	end_program_bonus(&condition, philo);
	return (0);
}
