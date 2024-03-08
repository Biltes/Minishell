/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 15:13:46 by pevieira          #+#    #+#             */
/*   Updated: 2023/04/28 19:12:40 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*p;

	p = NULL;
	if ((char)c == '\0')
		p = (char *)s + ft_strlen(s);
	else
	{
		while (*s != '\0')
		{
			if (*s == (char)c)
				p = (char *)s;
			s++;
		}
	}
	if (*s == (char)c)
		p = (char *)s;
	return (p);
}
