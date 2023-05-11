/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 09:17:11 by arabenst          #+#    #+#             */
/*   Updated: 2023/05/09 10:42:47 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	ft_init_mutexes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_amount)
	{
		if (pthread_mutex_init(&data->mtx_forks[i], NULL))
			break ;
		data->mtx_forks_count++;
		if (pthread_mutex_init(&data->philos[i].mtx_last_eaten, NULL))
			break ;
		data->philo_mtx_last_eaten_count++;
	}
	if (!pthread_mutex_init(&data->mtx_exit, NULL))
		data->mtx_exit_count++;
	if (data->mtx_forks_count != data->philo_amount
		|| data->philo_mtx_last_eaten_count != data->philo_amount
		|| data->mtx_exit_count != 1)
		return (ft_error(ERR_MUTEX_INIT), ft_destroy_mutexes(data),
			RETURN_FAILURE);
	return (RETURN_SUCCESS);
}

bool	ft_create_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_amount)
		if (pthread_create(&data->threads[i], NULL, &ft_routine,
				&data->philos[i]))
			return (ft_set_exit(data), ft_error(ERR_PTHREAD_CREATE),
				ft_join_threads(data, i + 1), RETURN_FAILURE);
	return (RETURN_SUCCESS);
}

bool	ft_join_threads(t_data *data, int amount)
{
	bool	joined;

	joined = true;
	while (--amount >= 0)
		if (pthread_join(data->threads[amount], NULL))
			joined = false;
	if (joined == false)
		return (ft_error(ERR_PTHREAD_JOIN), RETURN_FAILURE);
	return (RETURN_SUCCESS);
}

bool	ft_destroy_mutexes(t_data *data)
{
	bool	destroyed_forks;
	bool	destroyed_philo_mtx_last_eaten;
	bool	destroyed_mtx_exit;

	destroyed_forks = true;
	destroyed_philo_mtx_last_eaten = true;
	destroyed_mtx_exit = true;
	while (--data->mtx_forks_count >= 0)
		if (pthread_mutex_destroy(&data->mtx_forks[data->mtx_forks_count]))
			destroyed_forks = false;
	while (--data->philo_mtx_last_eaten_count >= 0)
		if (pthread_mutex_destroy(&data->philos[data->philo_mtx_last_eaten_count].mtx_last_eaten))
			destroyed_philo_mtx_last_eaten = false;
	if (data->mtx_exit_count == 1)
		if (pthread_mutex_destroy(&data->mtx_exit))
			destroyed_mtx_exit = false;
	if (destroyed_forks == false || destroyed_philo_mtx_last_eaten == false
		|| destroyed_philo_mtx_last_eaten == false)
		return (ft_error(ERR_MUTEX_DESTROY), RETURN_FAILURE);
	return (RETURN_SUCCESS);
}
