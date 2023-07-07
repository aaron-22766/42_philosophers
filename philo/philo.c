/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:24:16 by arabenst          #+#    #+#             */
/*   Updated: 2023/07/07 13:17:10 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	ft_get_input(t_data *data, int argc, char **argv)
{
	if (argc < 5)
		return (ft_error(ERR_TOO_FEW_ARGS), RETURN_FAILURE);
	if (argc > 6)
		return (ft_error(ERR_TOO_MANY_ARGS), RETURN_FAILURE);
	data->philo_amount = ft_atoi(argv[1]);
	if (data->philo_amount < 1)
		return (ft_error(ERR_ARG_PHILO), RETURN_FAILURE);
	data->tt_die = ft_atoi(argv[2]);
	if (data->tt_die < 1)
		return (ft_error(ERR_ARG_TT_DIE), RETURN_FAILURE);
	data->tt_eat = ft_atoi(argv[3]);
	if (data->tt_eat < 1)
		return (ft_error(ERR_ARG_TT_EAT), RETURN_FAILURE);
	data->tt_sleep = ft_atoi(argv[4]);
	if (data->tt_sleep < 1)
		return (ft_error(ERR_ARG_TT_SLEEP), RETURN_FAILURE);
	data->eat_limit = -1;
	if (argc == 6)
	{
		data->eat_limit = ft_atoi(argv[5]);
		if (data->eat_limit < 0)
			return (ft_error(ERR_ARG_EAT_LIMIT), RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}

static bool	ft_init_data(t_data *data)
{
	data->philos = malloc(data->philo_amount * sizeof(t_philo));
	if (!data->philos)
		return (RETURN_FAILURE);
	data->threads = malloc(data->philo_amount * sizeof(pthread_t));
	if (!data->threads)
		return (free(data->philos), RETURN_FAILURE);
	data->mtx_forks = malloc(data->philo_amount * sizeof(pthread_mutex_t));
	if (!data->mtx_forks)
		return (free(data->philos), free(data->threads), RETURN_FAILURE);
	return (RETURN_SUCCESS);
	data->exit = false;
}

static void	ft_set_table(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_amount)
		pthread_mutex_init(&data->mtx_forks[i], NULL);
	pthread_mutex_init(&data->mtx_exit, NULL);
	pthread_mutex_init(&data->mtx_printf, NULL);
	i = -1;
	while (++i < data->philo_amount)
	{
		data->philos[i].id = i + 1;
		data->philos[i].eat_count = 0;
		data->philos[i].mtx_fork_l = &data->mtx_forks[i];
		data->philos[i].mtx_fork_r
			= &data->mtx_forks[(i + 1) % data->philo_amount];
		pthread_mutex_init(&data->philos[i].mtx_eat_count, NULL);
		pthread_mutex_init(&data->philos[i].mtx_time_last_eaten, NULL);
		data->philos[i].data = data;
	}
}

static void	ft_clear_table(t_data *data)
{
	int	i;

	pthread_join(data->monitor_death, NULL);
	if (data->eat_limit > 0 && data->philo_amount > 1)
		pthread_join(data->monitor_eat_limit, NULL);
	i = -1;
	while (++i < data->philo_amount)
		pthread_join(data->threads[i], NULL);
	i = -1;
	while (++i < data->philo_amount)
	{
		pthread_mutex_destroy(&data->mtx_forks[i]);
		pthread_mutex_destroy(&data->philos[i].mtx_eat_count);
		pthread_mutex_destroy(&data->philos[i].mtx_time_last_eaten);
	}
	pthread_mutex_destroy(&data->mtx_exit);
	pthread_mutex_destroy(&data->mtx_printf);
	free(data->threads);
	free(data->mtx_forks);
	free(data->philos);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (ft_get_input(&data, argc, argv) == RETURN_FAILURE)
		return (EXIT_FAILURE);
	if (data.eat_limit == 0)
		return (EXIT_SUCCESS);
	if (ft_init_data(&data) == RETURN_FAILURE)
		return (ft_error(ERR_MEM), EXIT_FAILURE);
	ft_set_table(&data);
	if (ft_simulation(&data) == RETURN_FAILURE)
		return (ft_error(ERR_THREAD), ft_clear_table(&data), EXIT_FAILURE);
	return (ft_clear_table(&data), EXIT_SUCCESS);
}
