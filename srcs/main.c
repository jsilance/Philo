/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:12:48 by jusilanc          #+#    #+#             */
/*   Updated: 2023/04/28 03:48:20 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int				g_mail = 0;
pthread_mutex_t	g_mutex;

void	*ft_routine(void *arg)
{
	int	i;

	(void)arg;
	i = 0;
	while (i++ < 10000000)
	{
		pthread_mutex_lock(&g_mutex);
		g_mail++;
		pthread_mutex_unlock(&g_mutex);
	}
	pthread_exit(NULL);
}

int	main(int argc, char **argv)
{
	pthread_t	ptr;
	pthread_t	ptr2;
	t_philo		philo;

	if (ft_philo_init(&philo, argv, argc) == -1)
		return (1);
	pthread_mutex_init(&g_mutex, NULL);
	(void)argv;
	(void)argc;
	if (pthread_create(&ptr, NULL, ft_routine, (void *)"yolo\n"))
		return (1);
	if (pthread_create(&ptr2, NULL, ft_routine, (void *)"yolo1\n"))
		return (1);
	pthread_join(ptr, NULL);
	pthread_join(ptr2, NULL);
	pthread_mutex_destroy(&g_mutex);
	printf("[%u]\n", g_mail);
	return (0);
}
