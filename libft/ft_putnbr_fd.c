/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 19:41:12 by pevieira          #+#    #+#             */
/*   Updated: 2023/04/22 12:48:41 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	nbr;
	char		nbr_char;

	nbr = n;
	if (nbr < 0)
	{
		write(fd, "-", 1);
		nbr *= -1;
	}
	if (nbr >= 0 && nbr < 10)
	{
		nbr_char = nbr + '0';
		write(fd, &nbr_char, 1);
	}
	else
	{
		ft_putnbr_fd(nbr / 10, fd);
		nbr_char = (nbr % 10) + '0';
		write(fd, &nbr_char, 1);
	}
}
