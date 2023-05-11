/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:38:31 by arabenst          #+#    #+#             */
/*   Updated: 2023/05/09 10:31:23 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	ft_philos_should_end(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_amount)
	{
		if (ft_timer(ft_get_last_eaten(&data->philos[i])) >= data->die_time)
		{
			ft_print_state(&data->philos[i], "died");
			// if (data->philo_amount % 2)
			// 	pthread_mutex_unlock(&data->forks[data->philos[i].id
			// 		- !(data->philos[i].id) - 1]);
			return (true);
		}
	}
	return (false);
}

bool	ft_simulation(t_data *data)
{
	int	i;

	if (ft_init_mutexes(data) == RETURN_FAILURE)
		return (RETURN_FAILURE);
	gettimeofday(&data->tp_start, NULL);
	i = -1;
	while (++i < data->philo_amount)
		data->philos[i].tp_last_eaten = data->tp_start;
	if (ft_create_threads(data) == RETURN_FAILURE)
		return (RETURN_FAILURE);
	while (!ft_philos_should_end(data))
		ft_sleep(data, 1);
	ft_set_exit(data);
	if (ft_join_threads(data, data->philo_amount) == RETURN_FAILURE)
		return (RETURN_FAILURE);
	if (ft_destroy_mutexes(data) == RETURN_FAILURE)
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}
