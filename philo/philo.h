/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:23:08 by arabenst          #+#    #+#             */
/*   Updated: 2023/07/10 16:41:53 by arabenst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* ************************************************************************** */
/*                                  INCLUDES                                  */
/* ************************************************************************** */

# include <string.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

/* ************************************************************************** */
/*                                   ENUMS                                    */
/* ************************************************************************** */

enum e_return
{
	RETURN_SUCCESS,
	RETURN_FAILURE
};

enum e_errors
{
	ERR_MEM,
	ERR_TOO_FEW_ARGS,
	ERR_TOO_MANY_ARGS,
	ERR_ARG_PHILO,
	ERR_ARG_TT_DIE,
	ERR_ARG_TT_EAT,
	ERR_ARG_TT_SLEEP,
	ERR_ARG_EAT_LIMIT,
	ERR_THREAD
};

enum e_philo_vars
{
	TIME_LAST_EATEN,
	INCREMENT_EAT_COUNT
};

/* ************************************************************************** */
/*                                  STRUCTS                                   */
/* ************************************************************************** */

struct	s_philo;
struct	s_data;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	u_int64_t		time_last_eaten;
	pthread_mutex_t	*mtx_fork_l;
	pthread_mutex_t	*mtx_fork_r;
	pthread_mutex_t	mtx_eat_count;
	pthread_mutex_t	mtx_time_last_eaten;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				philo_amount;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				eat_limit;
	bool			exit;
	u_int64_t		time_start;
	struct s_philo	*philos;
	pthread_mutex_t	mtx_exit;
	pthread_mutex_t	mtx_printf;
	pthread_mutex_t	*mtx_forks;
	pthread_t		*threads;
	pthread_t		monitor_death;
	pthread_t		monitor_eat_limit;
}	t_data;

/* ************************************************************************** */
/*                                 FUNCTIONS                                  */
/* ************************************************************************** */

// philo.c

// simulation.c
bool		ft_simulation(t_data *data);

// routine.c
void		*ft_routine(void *arg);

// mtx_vars.c
bool		ft_is_exit(t_data *data);
void		ft_set_exit(t_data *data);
bool		ft_set_time_last_eaten(t_philo *philo);
bool		ft_increment_eat_count(t_philo *philo);
int			ft_get_eat_count(t_philo *philo);

// utils.c
u_int64_t	ft_get_time(u_int64_t relative);
void		ft_wait(u_int64_t ms);
void		ft_print_state(t_philo *philo, const char *state);
size_t		ft_strlen(const char *s);
int			ft_atoi(const char *str);

// error.c
void		ft_error(char code);

#endif
