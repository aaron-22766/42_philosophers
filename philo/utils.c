/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 10:36:30 by arabenst          #+#    #+#             */
/*   Updated: 2023/07/05 18:10:23 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	if (str[i] == '-')
		return (-1);
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result);
}

void	ft_print_state(t_philo *philo, const char *state)
{
	pthread_mutex_lock(&philo->data->mtx_printf);
	if (ft_get_exit(philo->data) == false)
		printf("%lld %d %s\n",
			ft_get_time(philo->data->time_start), philo->id, state);
	pthread_mutex_unlock(&philo->data->mtx_printf);
}

uint64_t	ft_get_time(uint64_t start)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * (uint64_t)1000) + (now.tv_usec / 1000) - start);
}

void	ft_wait(uint64_t ms)
{
	u_int64_t	start;

	start = ft_get_time(0);
	while (ft_get_time(start) < ms)
		usleep(500);
}
