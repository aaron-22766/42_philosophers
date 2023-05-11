/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:23:08 by arabenst          #+#    #+#             */
/*   Updated: 2023/05/09 10:32:53 by arabenst         ###   ########.fr       */
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
/*                                  DEFINES                                   */
/* ************************************************************************** */

# define RETURN_SUCCESS 0
# define RETURN_FAILURE 1

# define ERR_MEM 0
# define ERR_TOO_FEW_ARGS 1
# define ERR_TOO_MANY_ARGS 2
# define ERR_ARG_PHILO 3
# define ERR_ARG_DIE_TIME 4
# define ERR_ARG_EAT_TIME 5
# define ERR_ARG_SLEEP_TIME 6
# define ERR_ARG_EAT_LIMIT 7
# define ERR_PTHREAD_CREATE 8
# define ERR_PTHREAD_JOIN 9
# define ERR_MUTEX_INIT 10
# define ERR_MUTEX_DESTROY 11

/* ************************************************************************** */
/*                                  STRUCTS                                   */
/* ************************************************************************** */

struct	s_philo;
struct	s_data;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	struct timeval	tp_last_eaten;
	pthread_mutex_t	mtx_last_eaten;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				philo_amount;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				eat_limit;
	bool			exit;
	pthread_mutex_t	mtx_exit;
	int				mtx_exit_count;
	struct timeval	tp_start;
	struct s_philo	*philos;
	int				philo_mtx_last_eaten_count;
	pthread_t		*threads;
	pthread_mutex_t	*mtx_forks;
	int				mtx_forks_count;
}	t_data;

/* ************************************************************************** */
/*                                 FUNCTIONS                                  */
/* ************************************************************************** */

// philo.c

// simulation.c
bool			ft_simulation(t_data *data);

// thread.c
bool			ft_init_mutexes(t_data *data);
bool			ft_create_threads(t_data *data);
bool			ft_join_threads(t_data *data, int amount);
bool			ft_destroy_mutexes(t_data *data);

// routine.c
void			*ft_routine(void *arg);

// protected_values.c
void			ft_set_exit(t_data *data);
bool			ft_is_exit(t_data *data);
void			ft_set_last_eaten(t_philo *philo);
struct timeval	ft_get_last_eaten(t_philo *philo);

// utils.c
size_t			ft_strlen(const char *s);
int				ft_atoi(const char *str);
void			ft_print_state(t_philo *philo, const char *state);
int				ft_timer(struct timeval tp_start);
void			ft_sleep(t_data *data, int ms);
void			ft_free_data(t_data *data);

// error.c
void			ft_error(char code);

#endif
