/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 09:56:32 by pehenri2          #+#    #+#             */
/*   Updated: 2024/08/08 19:43:03 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*ascii;
	int		len;
	long	nbr;

	len = ft_nbrlen(n, 10);
	nbr = n;
	if (nbr < 0)
	{
		nbr = -nbr;
		len++;
	}
	ascii = ft_dalloc(sizeof(char), (len + 1));
	if (ascii == NULL)
		return (NULL);
	ascii[len] = '\0';
	while (len > 0)
	{
		ascii[--len] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}
	if (n < 0)
		ascii[0] = '-';
	return (ascii);
}
