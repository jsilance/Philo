/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:12:48 by jusilanc          #+#    #+#             */
/*   Updated: 2023/04/27 14:28:18 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

int	main(int argc, char **argv)
{
	pthread_t	ptr;
	pthread_t	ptr2;

	(void)argv;
	(void)argc;
	if (pthread_create(&ptr, NULL, (void *)printf, (void *)"yolo\n"))
		return (1);
	if (pthread_create(&ptr2, NULL, (void *)printf, (void *)"yolo1\n"))
		return (1);
	pthread_join(ptr, NULL);
	pthread_join(ptr2, NULL);
	return (0);
}
