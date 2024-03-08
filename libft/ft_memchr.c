/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 15:55:22 by pevieira          #+#    #+#             */
/*   Updated: 2023/04/28 19:16:22 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*s_cast;

	s_cast = (char *) s;
	while (n-- > 0)
	{
		if (*s_cast == (char)c)
			return (s_cast);
		s_cast++;
	}
	return (NULL);
}
