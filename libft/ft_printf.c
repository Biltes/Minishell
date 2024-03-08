/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:54:46 by pevieira          #+#    #+#             */
/*   Updated: 2023/11/19 23:45:27 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_write_special(va_list args, const char s)
{
	if (s == 'c')
		return (ft_putchar(va_arg(args, int)));
	if (s == 's')
		return (ft_putstr(va_arg(args, char *)));
	if (s == 'p')
		return (ft_printpointer(va_arg(args, unsigned long long)));
	if (s == 'd' || s == 'i')
		return (ft_putdecimal(va_arg(args, int)));
	if (s == 'u')
		return (ft_unsigned_putdecimal(va_arg(args, unsigned int)));
	if (s == 'x' || s == 'X')
		return (ft_hexparam(va_arg(args, unsigned int), s));
	if (s == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		result;

	i = 0;
	result = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			result += ft_write_special(args, str[++i]);
			i++;
		}
		else
			result += ft_putchar(str[i++]);
	}
	va_end(args);
	return (result);
}
