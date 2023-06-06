/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_eat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:39:55 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/06 16:10:39 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	philo_eat(t_philo *philo, struct timeval *last_eat,
		pthread_mutex_t *right_fork, int *right_fork_available)
{
	if (ft_is_dead(philo->mut_dead, philo->death))
		return (-1);
	ft_mut_print(philo->id, "is eating", philo->printing);
	ft_sleep(philo->time_to_eat);
	ft_philo_releaser(right_fork, right_fork_available, &philo->total_fork);
	ft_philo_releaser(&philo->left_fork, &philo->fork_available,
			&philo->total_fork);
	gettimeofday(last_eat, NULL);
	return (0);
}
