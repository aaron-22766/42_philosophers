/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:38:31 by arabenst          #+#    #+#             */
/*   Updated: 2023/07/05 18:41:47 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*ft_one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->mtx_fork_l);
	ft_print_state(philo, "has taken a fork");
	while (ft_get_exit(philo->data) == false)
		usleep(10);
	pthread_mutex_unlock(philo->mtx_fork_l);
	return (NULL);
}

static void	ft_take_fork(t_philo *philo, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	ft_print_state(philo, "has taken a fork");
}

static void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->data->philo_amount == 1)
		return (ft_one_philo(philo));
	while (ft_get_exit(philo->data) == false && (!philo->data->eat_limit
			|| ft_get_eat_count(philo) < philo->data->eat_limit))
	{
		if (philo->id % 2 == 0)
			usleep(philo->data->tt_eat / 2);
		ft_take_fork(philo, philo->mtx_fork_l);
		ft_take_fork(philo, philo->mtx_fork_r);
		ft_print_state(philo, "is eating");
		ft_set_time_last_eaten(philo);
		ft_wait(philo->data->tt_eat);
		pthread_mutex_unlock(philo->mtx_fork_l);
		pthread_mutex_unlock(philo->mtx_fork_r);
		ft_print_state(philo, "is sleeping");
		ft_increment_eat_count(philo);
		ft_wait(philo->data->tt_sleep);
		ft_print_state(philo, "is thinking");
	}
	return (NULL);
}

static void	ft_monitor_philos(t_data *data)
{
	int	philos_eaten;
	int	i;

	while (true)
	{
		philos_eaten = 0;
		i = -1;
		while (++i < data->philo_amount)
		{
			if (ft_get_time(ft_get_time_last_eaten(&data->philos[i]))
				> (uint64_t)data->tt_die)
			{
				ft_print_state(&data->philos[i], "died");
				return ;
			}
			if (data->eat_limit
				&& ft_get_eat_count(&data->philos[i]) >= data->eat_limit)
				philos_eaten++;
		}
		if (philos_eaten == data->philo_amount)
			return ;
	}
}

bool	ft_simulation(t_data *data)
{
	int	i;

	data->time_start = ft_get_time(0);
	i = -1;
	while (++i < data->philo_amount)
		data->philos[i].time_last_eaten = data->time_start;
	i = -1;
	while (++i < data->philo_amount)
		if (pthread_create(&data->threads[i], NULL, &ft_routine,
				&data->philos[i]))
			return (ft_error(ERR_PTHREAD_CREATE), RETURN_FAILURE);
	ft_monitor_philos(data);
	pthread_mutex_lock(&data->mtx_exit);
	data->exit = true;
	pthread_mutex_unlock(&data->mtx_exit);
	return (RETURN_SUCCESS);
}
