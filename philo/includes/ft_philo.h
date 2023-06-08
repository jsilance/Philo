/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:13:23 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/08 11:10:05 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PHILO_H
# define FT_PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

enum				e_state
{
	EAT = 1,
	SLEEP,
	THINKING
};

typedef struct s_philo
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_to_eat;
	int				id;
	int				total_fork;
	pthread_mutex_t	left_fork;
	int				fork_available;
	struct s_philo	*philos;
	pthread_mutex_t	*printing;
	pthread_mutex_t	*mut_dead;
	int				*death;
}					t_philo;

typedef struct s_philo_param
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_to_eat;
	pthread_t		*thread_p;
	t_philo			*philos;
	pthread_mutex_t	printing;
	pthread_mutex_t	mut_dead;
	int				death;
}					t_philo_param;

typedef struct s_philo_state
{
	struct timeval	last_eat;
	struct timeval	end;
	int				state;
	int				thinking;
	int				thinking_ret;
	t_philo			*philo;
	t_philo			*right_philo;
}					t_philo_state;

int					ft_philo_param_init(t_philo_param *philo, char **argv,
						int argc);
int					ft_atoi(const char *str);
int					ft_str_isdigit(const char *str);
int					ft_isdigit(int c);
void				*ft_philosophe(void *ptr);
t_philo				*ft_philo_create(t_philo_param *philo_param, int i);

int					ft_philo_destructor(t_philo_param *ptr, int ret);

void				ft_sleep(int ms);
unsigned long		ft_time_to_ms(struct timeval data);
int					ft_mut_print(int id, char *action,
						pthread_mutex_t *mut_print);
int					ft_is_dead(pthread_mutex_t *mut_dead, int *death);

int					philo_eat(t_philo *philo, struct timeval *last_eat,
						pthread_mutex_t *right_fork, int *right_fork_available);
int					philo_sleep(t_philo *philo, int *state);
int					philo_thinking(t_philo *philo, int *thinking,
						pthread_mutex_t *right_fork, int *right_fork_available);
int					ft_philo_taker(pthread_mutex_t *fork, int *state_of_fork,
						int *total_fork);
int					ft_philo_releaser(pthread_mutex_t *fork, int *state_of_fork,
						int *total_fork);

int					thinking_part(t_philo_state *p);
int					eating_part(t_philo *philo, struct timeval *last_eat,
						t_philo *right_philo, int *state);
int					ft_is_dead(pthread_mutex_t *mut_dead, int *death);
int					death_part(t_philo_state *p);
int					ft_time_passed(struct timeval start, struct timeval end);

#endif
