/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 11:03:19 by pedroalves        #+#    #+#             */
/*   Updated: 2023/04/22 11:56:16 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_string;
	size_t	total_lenghts;

	total_lenghts = ft_strlen(s1) + ft_strlen(s2);
	new_string = (char *) malloc(sizeof(char) * (total_lenghts + 1));
	if (!new_string)
		return (NULL);
	while (*s1)
		*new_string++ = *s1++;
	while (*s2)
		*new_string++ = *s2++;
	*new_string = '\0';
	return (new_string - total_lenghts);
}
