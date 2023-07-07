/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:38:31 by arabenst          #+#    #+#             */
/*   Updated: 2023/07/07 14:09:57 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static u_int64_t	ft_get_time_last_eaten(t_philo *philo)
{
	u_int64_t	time_last_eaten;

	pthread_mutex_lock(&philo->mtx_time_last_eaten);
	time_last_eaten = philo->time_last_eaten;
	pthread_mutex_unlock(&philo->mtx_time_last_eaten);
	return (time_last_eaten);
}

static void	*ft_monitor_death(void *arg)
{
	t_data	*data;
	int		i;

	data = arg;
	while (!ft_is_exit(data))
	{
		i = -1;
		while (++i < data->philo_amount)
		{
			if (ft_get_time(ft_get_time_last_eaten(&data->philos[i]))
				> (u_int64_t)data->tt_die)
				return (ft_print_state(&data->philos[i], "died"),
					ft_set_exit(data), NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

static	int	ft_get_eat_count(t_philo *philo)
{
	int	eat_count;

	pthread_mutex_lock(&philo->mtx_eat_count);
	eat_count = philo->eat_count;
	pthread_mutex_unlock(&philo->mtx_eat_count);
	return (eat_count);
}

static void	*ft_monitor_eat_limit(void *arg)
{
	t_data	*data;
	int		i;

	data = arg;
	while (!ft_is_exit(data))
	{
		i = -1;
		while (++i < data->philo_amount)
			if (ft_get_eat_count(&data->philos[i]) < data->eat_limit)
				break ;
		if (i == data->philo_amount)
			return (ft_set_exit(data), NULL);
		usleep(1000);
	}
	return (NULL);
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
		if (pthread_create(&data->threads[i], NULL,
				&ft_routine, &data->philos[i]))
			return (RETURN_FAILURE);
	if (pthread_create(&data->monitor_death, NULL, &ft_monitor_death, data)
		|| (data->eat_limit > 0 && data->philo_amount > 1
			&& pthread_create(&data->monitor_eat_limit, NULL,
				&ft_monitor_eat_limit, data)))
		return (RETURN_FAILURE);
	return (RETURN_SUCCESS);
}
