/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 18:29:46 by pevieira          #+#    #+#             */
/*   Updated: 2023/11/19 23:48:54 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_hexlen(unsigned long long nbr)
{
	int	len;

	len = 0;
	while (nbr != 0)
	{
		len++;
		nbr /= 16;
	}
	return (len);
}

void	ft_hexconvertion(unsigned long long nbr, const char s)
{
	char	n;

	if (nbr >= 16)
	{
		ft_hexconvertion(nbr / 16, s);
		ft_hexconvertion(nbr % 16, s);
	}
	if (nbr <= 9)
	{
		n = nbr + '0';
		write(1, &n, 1);
	}
	if (nbr >= 10 && nbr <= 15)
	{
		if (s == 'X')
			n = nbr - 10 + 'A';
		else
			n = nbr - 10 + 'a';
		write(1, &n, 1);
	}
}

int	ft_printpointer(unsigned long long nbr)
{
	int	hlen;

	hlen = 2;
	if (nbr == 0)
		return (ft_putstr("(nil)"));
	write(1, "0x", 2);
	ft_hexconvertion(nbr, 'x');
	return (hlen += ft_hexlen(nbr));
}

int	ft_hexparam(unsigned int nbr, const char s)
{
	if (nbr == 0)
		return (ft_putchar('0'));
	ft_hexconvertion(nbr, s);
	return (ft_hexlen(nbr));
}
