/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:24:16 by arabenst          #+#    #+#             */
/*   Updated: 2023/05/09 10:29:52 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_init_data(t_data *data)
{
	data->eat_limit = 0;
	data->exit = false;
	data->philos = NULL;
	data->threads = NULL;
	data->mtx_forks = NULL;
}

static bool	ft_get_input(t_data *data, int argc, char **argv)
{
	if (argc < 5)
		return (ft_error(ERR_TOO_FEW_ARGS), RETURN_FAILURE);
	if (argc > 6)
		return (ft_error(ERR_TOO_MANY_ARGS), RETURN_FAILURE);
	data->philo_amount = ft_atoi(argv[1]);
	if (data->philo_amount < 1)
		return (ft_error(ERR_ARG_PHILO), RETURN_FAILURE);
	data->die_time = ft_atoi(argv[2]);
	if (data->die_time < 1)
		return (ft_error(ERR_ARG_DIE_TIME), RETURN_FAILURE);
	data->eat_time = ft_atoi(argv[3]);
	if (data->eat_time < 1)
		return (ft_error(ERR_ARG_EAT_TIME), RETURN_FAILURE);
	data->sleep_time = ft_atoi(argv[4]);
	if (data->sleep_time < 1)
		return (ft_error(ERR_ARG_SLEEP_TIME), RETURN_FAILURE);
	if (argc == 6)
	{
		data->eat_limit = ft_atoi(argv[5]);
		if (data->eat_limit < 0)
			return (ft_error(ERR_ARG_EAT_LIMIT), RETURN_FAILURE);
	}
	return (RETURN_SUCCESS);
}

static bool	ft_init_table(t_data *data)
{
	int	i;

	data->philos = malloc(data->philo_amount * sizeof(t_philo));
	data->threads = malloc(data->philo_amount * sizeof(pthread_t));
	data->mtx_forks = malloc(data->philo_amount * sizeof(pthread_mutex_t));
	if (!data->philos || !data->threads || !data->mtx_forks)
		return (ft_error(ERR_MEM), RETURN_FAILURE);
	i = -1;
	while (++i < data->philo_amount)
	{
		data->philos[i].id = i + 1;
		data->philos[i].eat_count = 0;
		data->philos[i].data = data;
		data->philo_mtx_last_eaten_count = 0;
		data->mtx_exit_count = 0;
		data->mtx_forks_count = 0;
	}
	return (RETURN_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	data;

	ft_init_data(&data);
	if (ft_get_input(&data, argc, argv) == RETURN_FAILURE)
		return (RETURN_FAILURE);
	if (ft_init_table(&data) == RETURN_FAILURE)
		return (ft_free_data(&data), RETURN_FAILURE);
	if (ft_simulation(&data) == RETURN_FAILURE)
		return (ft_free_data(&data), RETURN_FAILURE);
	// printf("____________________________\n%d threads took %d ms to run\n", data.philo_amount, ft_timer(&data.tp_start));
	return (ft_free_data(&data), RETURN_SUCCESS);
}
