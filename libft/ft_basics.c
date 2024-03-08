/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_basics.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 15:43:23 by pevieira          #+#    #+#             */
/*   Updated: 2023/11/19 23:47:51 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (ft_putstr("(null)"));
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_putdecimal(int nbr)
{
	int		decimal_len;
	char	*conversion;

	conversion = ft_itoa(nbr);
	decimal_len = ft_putstr(conversion);
	free(conversion);
	return (decimal_len);
}

int	ft_unsigned_putdecimal(unsigned int nbr)
{
	int		udecimal_len;
	char	*uconversion;

	uconversion = ft_uitoa(nbr);
	udecimal_len = ft_putstr(uconversion);
	free(uconversion);
	return (udecimal_len);
}
