/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_think.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:46:03 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/06 16:00:59 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	ft_philo_releaser(pthread_mutex_t *fork, int *state_of_fork,
		int *total_fork)
{
	if (pthread_mutex_lock(fork) == -1)
		return (-1);
	if (*state_of_fork == 0)
	{
		*state_of_fork = 1;
		(*total_fork)--;
	}
	if (pthread_mutex_unlock(fork) == -1)
		return (-1);
	return (0);
}

int	ft_philo_taker(pthread_mutex_t *fork, int *state_of_fork, int *total_fork)
{
	if (pthread_mutex_lock(fork) == -1)
		return (-1);
	if (*state_of_fork == 1)
	{
		*state_of_fork = 0;
		(*total_fork)++;
	}
	if (pthread_mutex_unlock(fork) == -1)
		return (-1);
	return (0);
}

int	philo_thinking(t_philo *philo, int *thinking, pthread_mutex_t *right_fork,
		int *right_fork_available)
{
	if (ft_is_dead(philo->mut_dead, philo->death))
		return (-1);
	if (*thinking == 0)
	{
		ft_mut_print(philo->id, "is thinking", philo->printing);
		*thinking = 1;
	}
	if (ft_philo_taker(right_fork, right_fork_available,
			&philo->total_fork) == 0)
	{
		if (ft_philo_taker(&philo->left_fork, &philo->fork_available,
				&philo->total_fork) == 0)
		{
			ft_mut_print(philo->id, "has taken a fork", philo->printing);
			ft_mut_print(philo->id, "has taken a fork", philo->printing);
		}
		else
		{
			ft_philo_releaser(right_fork, right_fork_available,
					&philo->total_fork);
			return (1);
		}
		*thinking = 0;
	}
	return (0);
}