/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 09:21:36 by arabenst          #+#    #+#             */
/*   Updated: 2023/05/09 10:30:21 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	ft_take_fork(t_philo *philo, int index)
{
	if (ft_is_exit(philo->data))
		return (true);
	pthread_mutex_lock(&philo->data->mtx_forks[index]);
	if (ft_is_exit(philo->data))
	{
		pthread_mutex_unlock(&philo->data->mtx_forks[index]);
		return (true);
	}
	ft_print_state(philo, "has taken a fork");
	return (ft_is_exit(philo->data));
}

static void	ft_philo_think(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	ft_print_state(philo, "is thinking");
	if (ft_take_fork(philo, philo->id - 1))
		return ;
	if (data->philo_amount == 1)
	{
		pthread_mutex_unlock(&data->mtx_forks[philo->id - 1]);
		while (!ft_is_exit(philo->data))
			;
	}
	else
		if (ft_take_fork(philo, philo->id % data->philo_amount))
			return ;
}

static void	ft_philo_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	ft_set_last_eaten(philo);
	ft_print_state(philo, "is eating");
	ft_sleep(data, data->eat_time);
	pthread_mutex_unlock(&data->mtx_forks[philo->id - 1]);
	pthread_mutex_unlock(&data->mtx_forks[philo->id % data->philo_amount]);
	philo->eat_count++;
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	while (!ft_is_exit(philo->data))
	{
		ft_philo_think(philo);
		if (ft_is_exit(philo->data))
			return (NULL);
		ft_philo_eat(philo);
		if (ft_is_exit(philo->data))
			return (NULL);
		ft_print_state(philo, "is sleeping");
		ft_sleep(philo->data, philo->data->sleep_time);
	}
	return (NULL);
}
