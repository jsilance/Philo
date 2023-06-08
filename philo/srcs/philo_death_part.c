/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_death_part.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 19:35:19 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/08 18:46:08 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	ft_is_dead(pthread_mutex_t *mut_dead, int *death)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(mut_dead);
	if (*death != 0)
		ret = 1;
	pthread_mutex_unlock(mut_dead);
	return (ret);
}

int	death_part(t_philo_state *p)
{
	gettimeofday(&p->end, NULL);
	if (ft_time_passed(p->last_eat, p->end) > p->philo->time_to_die)
	{
		if (ft_is_dead(p->philo->mut_dead, p->philo->death))
			return (-1);
		ft_mut_print(p->philo->id, "died", p->philo->printing);
		*p->philo->death = 1;
		return (-1);
	}
	return (0);
}
