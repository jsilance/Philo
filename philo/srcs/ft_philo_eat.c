/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo_eat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@s19.be>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 13:39:55 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/12 15:48:01 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	philo_eat(t_philo_state *p)
{
	if (ft_is_dead(p->philo->mut_dead, p->philo->death))
		return (-1);
	if (ft_mut_print(p->philo->id, "is eating", p->philo->printing) == -1)
		return (-1);
	gettimeofday(&p->last_eat, NULL);
	ft_sleep(p->philo->time_to_eat, p);
	ft_philo_releaser(&p->right_philo->left_fork,
		&p->right_philo->fork_available, &p->philo->total_fork);
	ft_philo_releaser(&p->philo->left_fork, &p->philo->fork_available,
		&p->philo->total_fork);
	return (0);
}

int	eating_part(t_philo_state *p)
{
	if (p->philo->nb_to_eat > 0)
		p->philo->nb_to_eat--;
	else if (p->philo->nb_to_eat == 0)
		return (-1);
	if (philo_eat(p) == -1)
		return (-1);
	p->state = SLEEP;
	return (0);
}
