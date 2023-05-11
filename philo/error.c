/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:00:18 by arabenst          #+#    #+#             */
/*   Updated: 2023/05/09 10:36:20 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_puterror(const char *fault, const char *expectation)
{
	if (fault && ft_strlen(fault))
		printf("\nERROR!\n%s", fault);
	if (expectation && ft_strlen(expectation))
		printf(" Expected: %s", expectation);
	printf("\n\n");
}

static void	ft_arg_error(char err)
{
	printf("\nERROR!\nInvalid argument ");
	if (err == ERR_ARG_PHILO)
		printf("'number_of_philosophers'(1)");
	else if (err == ERR_ARG_DIE_TIME)
		printf("'time_to_die'(2)");
	else if (err == ERR_ARG_EAT_TIME)
		printf("'time_to_eat'(3)");
	else if (err == ERR_ARG_SLEEP_TIME)
		printf("'time_to_sleep'(4)");
	if (err == ERR_ARG_EAT_LIMIT)
	{
		printf("'number_of_times_each_philosopher_must_eat'(5)");
		ft_puterror("", "A positive int.");
	}
	else
		ft_puterror("", "A non-negative int.");
}

void	ft_error(char err)
{
	if (err == ERR_MEM)
		ft_puterror("Memory allocation failed!", "");
	else if (err == ERR_TOO_FEW_ARGS)
		ft_puterror("Too few arguments!", "4 or 5");
	else if (err == ERR_TOO_MANY_ARGS)
		ft_puterror("Too many arguments!", "4 or 5");
	else if (err >= ERR_ARG_PHILO && err <= ERR_ARG_EAT_LIMIT)
		ft_arg_error(err);
	else if (err == ERR_PTHREAD_CREATE)
		ft_puterror("Failed to create threads!", "");
	else if (err == ERR_PTHREAD_JOIN)
		ft_puterror("Failed to join threads!", "");
	else if (err == ERR_MUTEX_INIT)
		ft_puterror("Failed to initialize mutexes!", "");
	else if (err == ERR_MUTEX_DESTROY)
		ft_puterror("Failed to destroy mutexes!", "");
}
