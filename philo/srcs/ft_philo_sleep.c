/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_sleep.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:42:42 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/09 12:14:07 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

void	ft_sleep(int ms)
{
	struct timeval	start;
	struct timeval	current;

	gettimeofday(&start, NULL);
	gettimeofday(&current, NULL);
	while ((ft_time_to_ms(current) - ft_time_to_ms(start)) < (unsigned long)ms)
	{
		usleep(50);
		gettimeofday(&current, NULL);
	}
}

int	philo_sleep(t_philo *philo, int *state)
{
	if (ft_is_dead(philo->mut_dead, philo->death)
		|| ft_mut_print(philo->id, "is sleeping", philo->printing))
		return (-1);
	ft_sleep(philo->time_to_sleep);
	*state = THINKING;
	return (0);
}
