/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophe_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 22:50:55 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/07 17:31:51 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	ft_philo_destructor(t_philo_param *ptr)
{
	int	i;

	i = 0;
	ft_sleep(100);
	while (ptr->philos && ptr->philos[i].id)
		pthread_mutex_destroy(&ptr->philos[i++].left_fork);
	pthread_mutex_destroy(&ptr->printing);
	pthread_mutex_destroy(&ptr->mut_dead);
	free(ptr->philos);
	free(ptr->thread_p);
	return (0);
}

t_philo	*ft_philo_create(t_philo_param *philo_param)
{
	t_philo	*ptr;
	int		i;

	i = 0;
	ptr = (t_philo *)malloc(sizeof(t_philo) * (philo_param->nb_philo + 1));
	if (!ptr)
		return (NULL);
	while (i < philo_param->nb_philo)
	{
		pthread_mutex_init(&ptr[i].left_fork, NULL);
		ptr[i].id = i + 1;
		ptr[i].nb_philo = philo_param->nb_philo;
		ptr[i].time_to_die = philo_param->time_to_die;
		ptr[i].time_to_eat = philo_param->time_to_eat;
		ptr[i].time_to_sleep = philo_param->time_to_sleep;
		ptr[i].nb_to_eat = philo_param->nb_to_eat;
		ptr[i].philos = philo_param->philos;
		ptr[i].printing = &philo_param->printing;
		ptr[i].mut_dead = &philo_param->mut_dead;
		ptr[i].death = &philo_param->death;
		ptr[i].fork_available = 1;
		ptr[i++].total_fork = 0;
	}
	ptr[i].id = 0;
	return (ptr);
}
