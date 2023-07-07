/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 12:00:18 by arabenst          #+#    #+#             */
/*   Updated: 2023/07/07 09:38:59 by arabenst         ###   ########.fr       */
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
	printf("\nERROR!\nInvalid argument %d", err - 2);
	if (err == ERR_ARG_PHILO)
		printf("(number_of_philosophers)");
	else if (err == ERR_ARG_TT_DIE)
		printf("(time_to_die)");
	else if (err == ERR_ARG_TT_EAT)
		printf("(time_to_eat)");
	else if (err == ERR_ARG_TT_SLEEP)
		printf("(time_to_sleep)");
	if (err == ERR_ARG_EAT_LIMIT)
	{
		printf("(number_of_times_each_philosopher_must_eat)");
		ft_puterror("", "A non-negative integer");
	}
	else
		ft_puterror("", "A positive integer");
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
	else if (err == ERR_THREAD)
		ft_puterror("Failed to create threads!", "");
}
