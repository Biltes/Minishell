/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 17:20:52 by pevieira          #+#    #+#             */
/*   Updated: 2023/04/20 19:10:09 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*duplicate;
	size_t	lenght;

	lenght = ft_strlen(str);
	duplicate = (char *) malloc (sizeof(char) * (lenght + 1));
	if (!duplicate)
		return (NULL);
	ft_strlcpy(duplicate, str, lenght + 1);
	return (duplicate);
}
