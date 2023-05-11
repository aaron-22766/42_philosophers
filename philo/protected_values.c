/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected_values.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 09:42:10 by arabenst          #+#    #+#             */
/*   Updated: 2023/05/09 09:47:24 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_set_exit(t_data *data)
{
	pthread_mutex_lock(&data->mtx_exit);
	data->exit = true;
	pthread_mutex_unlock(&data->mtx_exit);
}

bool	ft_is_exit(t_data *data)
{
	bool	exit;

	pthread_mutex_lock(&data->mtx_exit);
	exit = data->exit;
	pthread_mutex_unlock(&data->mtx_exit);
	return (exit);
}

void	ft_set_last_eaten(t_philo *philo)
{
	pthread_mutex_lock(&philo->mtx_last_eaten);
	gettimeofday(&philo->tp_last_eaten, NULL);
	pthread_mutex_unlock(&philo->mtx_last_eaten);
}

struct timeval	ft_get_last_eaten(t_philo *philo)
{
	struct timeval	last_eaten;

	pthread_mutex_lock(&philo->mtx_last_eaten);
	last_eaten = philo->tp_last_eaten;
	pthread_mutex_unlock(&philo->mtx_last_eaten);
	return (last_eaten);
}
