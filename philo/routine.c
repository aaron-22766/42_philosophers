/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 09:28:37 by arabenst          #+#    #+#             */
/*   Updated: 2023/07/07 14:35:33 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*ft_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->mtx_fork_l);
	ft_print_state(philo, "has taken a fork");
	while (!ft_is_exit(philo->data))
		usleep(10);
	pthread_mutex_unlock(philo->mtx_fork_l);
	return (NULL);
}

static void	ft_take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->mtx_fork_l);
		ft_print_state(philo, "has taken a fork");
		pthread_mutex_lock(philo->mtx_fork_r);
		ft_print_state(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->mtx_fork_r);
		ft_print_state(philo, "has taken a fork");
		pthread_mutex_lock(philo->mtx_fork_l);
		ft_print_state(philo, "has taken a fork");
	}
}

static void	ft_put_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->mtx_fork_l);
		pthread_mutex_unlock(philo->mtx_fork_r);
	}
	else
	{
		pthread_mutex_unlock(philo->mtx_fork_r);
		pthread_mutex_unlock(philo->mtx_fork_l);
	}
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->data->philo_amount == 1)
		return (ft_one_philo(philo));
	if (philo->id % 2)
		usleep(42);
	while (!ft_is_exit(philo->data))
	{
		ft_take_forks(philo);
		ft_print_state(philo, "is eating");
		ft_set_time_last_eaten(philo);
		if (ft_is_exit(philo->data))
			return (ft_put_forks(philo), NULL);
		ft_wait(philo->data->tt_eat);
		ft_put_forks(philo);
		ft_print_state(philo, "is sleeping");
		if (ft_increment_eat_count(philo) || ft_is_exit(philo->data))
			return (NULL);
		ft_wait(philo->data->tt_sleep);
		ft_print_state(philo, "is thinking");
		if ((philo->data->philo_amount % 2) && !ft_is_exit(philo->data))
			ft_wait(philo->data->tt_eat * 2 - philo->data->tt_sleep);
	}
	return (NULL);
}
