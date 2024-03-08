/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:25:26 by pevieira          #+#    #+#             */
/*   Updated: 2023/11/21 19:09:47 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*destcast;
	unsigned const char	*srccast;

	destcast = dest;
	srccast = src;
	if (destcast == NULL && srccast == NULL)
		return (NULL);
	if (destcast < srccast)
	{
		while (n-- > 0)
			*destcast++ = *srccast++;
	}
	else
	{
		destcast += n;
		srccast += n;
		while (n-- > 0)
			*(--destcast) = *(--srccast);
	}
	return (dest);
}
