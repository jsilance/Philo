/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:13:23 by jusilanc          #+#    #+#             */
/*   Updated: 2023/04/29 01:29:47 by jusilanc         ###   ########.fr       */
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

typedef struct s_philo
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_to_eat;
	int				id;
	pthread_mutex_t	left_fork;
	// int				left_fork;
	struct s_philo	*philos;
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
}					t_philo_param;

int					ft_philo_param_init(t_philo_param *philo, char **argv,
						int argc);
int					ft_atoi(const char *str);
int					ft_str_isdigit(const char *str);
int					ft_isdigit(int c);
void				*ft_philosophe(void *ptr);
t_philo				*ft_philo_create(t_philo_param *philo_param);

int					ft_philo_destructor(t_philo_param *ptr);

#endif
