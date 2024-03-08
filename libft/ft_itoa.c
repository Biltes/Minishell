/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:48:26 by pevieira          #+#    #+#             */
/*   Updated: 2023/04/22 12:04:23 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countdigits(long int nbr)
{
	int	nc;

	nc = 0;
	if (nbr <= 0)
	{
		nbr *= -1;
		nc++;
	}
	while (nbr > 0)
	{
		nc += 1;
		nbr /= 10;
	}
	return (nc);
}

static void	ft_putnumber(char *number, long int nbr, int ncount)
{
	if (nbr == 0)
		number[0] = '0';
	else if (nbr < 0)
	{
		number[0] = '-';
		nbr *= -1;
	}
	while (nbr > 0)
	{
		number[ncount - 1] = nbr % 10 + '0';
		nbr /= 10;
		ncount--;
	}
}

char	*ft_itoa(int n)
{
	long int	nbr;
	int			ncount;
	char		*number;

	nbr = n;
	ncount = ft_countdigits(nbr);
	number = (char *) malloc(sizeof(char) * (ncount + 1));
	if (!number)
		return (NULL);
	number[ncount] = '\0';
	ft_putnumber(number, nbr, ncount);
	return (number);
}
