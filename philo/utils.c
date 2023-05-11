/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 10:36:30 by arabenst          #+#    #+#             */
/*   Updated: 2023/05/09 10:33:59 by arabenst         ###   ########.fr       */
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
	printf("%d %d %s\n", ft_timer(philo->data->tp_start), philo->id, state);
}

int	ft_timer(struct timeval tp_start)
{
	struct timeval	tp_end;

	gettimeofday(&tp_end, NULL);
	return ((tp_end.tv_sec - tp_start.tv_sec) * 1000
		+ (tp_end.tv_usec - tp_start.tv_usec) / 1000);
}

void	ft_sleep(t_data *data, int ms)
{
	struct timeval	tp_start;

	gettimeofday(&tp_start, NULL);
	while (!ft_is_exit(data) && ft_timer(tp_start) < ms)
		usleep(5);
}

void	ft_free_data(t_data *data)
{
	free(data->philos);
	free(data->threads);
	free(data->mtx_forks);
	// system("leaks philo");
}
