/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:24:16 by arabenst          #+#    #+#             */
/*   Updated: 2023/07/05 18:43:08 by arabenst         ###   ########.fr       */
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
	if (argc == 6)
	{
		data->eat_limit = ft_atoi(argv[5]);
		if (data->eat_limit < 0)
			return (ft_error(ERR_ARG_EAT_LIMIT), RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}

static void	ft_init_philo(t_data *data, int i)
{
	data->philos[i].id = i + 1;
	data->philos[i].eat_count = 0;
	data->philos[i].mtx_fork_l = &data->mtx_forks[i];
	data->philos[i].mtx_fork_r
		= &data->mtx_forks[(i + 1) % data->philo_amount];
	data->philos[i].data = data;
}

static bool	ft_set_table(t_data *data)
{
	int	i;

	data->philos = malloc(data->philo_amount * sizeof(t_philo));
	data->threads = malloc(data->philo_amount * sizeof(pthread_t));
	data->mtx_forks = malloc(data->philo_amount * sizeof(pthread_mutex_t));
	if (!data->philos || !data->threads || !data->mtx_forks)
		return (ft_error(ERR_MEM), RETURN_FAILURE);
	i = -1;
	while (++i < data->philo_amount)
		if (pthread_mutex_init(&data->mtx_forks[i], NULL)
			|| pthread_mutex_init(&data->philos[i].mtx_eat_count, NULL)
			|| pthread_mutex_init(&data->philos[i].mtx_time_last_eaten, NULL))
			break ;
	if (i != data->philo_amount
		|| pthread_mutex_init(&data->mtx_exit, NULL)
		|| pthread_mutex_init(&data->mtx_printf, NULL))
		return (ft_error(ERR_MUTEX_INIT), RETURN_FAILURE);
	i = -1;
	while (++i < data->philo_amount)
		ft_init_philo(data, i);
	return (RETURN_SUCCESS);
}

static void	ft_clear_table(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_amount)
	{
		pthread_join(data->threads[i], NULL);
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

	data.eat_limit = 0;
	data.exit = false;
	data.philos = NULL;
	data.threads = NULL;
	data.mtx_forks = NULL;
	if (ft_get_input(&data, argc, argv) == RETURN_FAILURE)
		return (RETURN_FAILURE);
	if (ft_set_table(&data) == RETURN_FAILURE)
		return (ft_clear_table(&data), RETURN_FAILURE);
	if (ft_simulation(&data) == RETURN_FAILURE)
		return (ft_clear_table(&data), RETURN_FAILURE);
	return (ft_clear_table(&data), RETURN_SUCCESS);
}
