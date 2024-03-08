/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:08:09 by pevieira          #+#    #+#             */
/*   Updated: 2023/04/28 17:38:24 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*destcast;
	unsigned const char	*srccast;

	if (!dest && !src)
		return (NULL);
	destcast = (unsigned char *) dest;
	srccast = (unsigned const char *) src;
	while (n-- > 0)
		*destcast++ = *srccast++;
	return (dest);
}
