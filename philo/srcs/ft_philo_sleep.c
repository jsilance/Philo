/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_sleep.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:42:42 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/12 15:50:28 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	ft_sleep(int ms, t_philo_state *p)
{
	struct timeval	start;
	struct timeval	current;

	gettimeofday(&start, NULL);
	gettimeofday(&current, NULL);
	while ((ft_time_to_ms(current) - ft_time_to_ms(start)) < (unsigned long)ms)
	{
		if (ft_time_to_ms(current) - ft_time_to_ms(p->last_eat)
			> (unsigned long)p->philo->time_to_die)
			if (death_part(p) == -1)
				return ;
		usleep(50);
		gettimeofday(&current, NULL);
	}
}

int	philo_sleep(t_philo_state *p)
{
	if (ft_is_dead(p->philo->mut_dead, p->philo->death)
		|| ft_mut_print(p->philo->id, "is sleeping", p->philo->printing))
		return (-1);
	ft_sleep(p->philo->time_to_sleep, p);
	p->state = THINKING;
	return (0);
}
