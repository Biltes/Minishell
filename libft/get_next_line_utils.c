/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 11:48:43 by pevieira          #+#    #+#             */
/*   Updated: 2023/11/19 22:46:34 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_gnl(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	if (s[i] == (unsigned char) c)
		return ((char *)s + i);
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char) c)
			return ((char *)s + i);
		i++;
	}
	return (0);
}

char	*ft_strjoin_gnl(char *stash, char *temp)
{
	char	*dest;
	int		len;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!stash)
	{
		stash = malloc(sizeof(char) * 1);
		stash[0] = '\0';
	}
	if (!stash || !temp)
		return (NULL);
	len = ft_strlen_gnl(stash) + ft_strlen_gnl(temp) + 1;
	dest = malloc(sizeof(char) * len);
	if (!dest)
		return (NULL);
	while (stash[++i])
		dest[i] = stash[i];
	while (temp[++j])
		dest[i + j] = temp[j];
	dest[i + j] = '\0';
	free(stash);
	return (dest);
}

char	*ft_line_to_get(char *string)
{
	char	*line;
	size_t	i;
	size_t	j;

	i = 0;
	if (!string)
		return (NULL);
	while (string[i] && string[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	j = -1;
	while (++j <= i)
		line[j] = string[j];
	line[j] = '\0';
	return (line);
}

char	*ft_rest(char *string)
{
	char	*rest;
	int		len_total;
	int		len_first;
	int		j;

	len_first = 0;
	while (string[len_first] && string[len_first] != '\n')
		len_first++;
	if (!string[len_first] || string[len_first + 1] == '\0')
	{
		free(string);
		return (NULL);
	}
	len_total = ft_strlen_gnl(string);
	rest = malloc(sizeof(char) * (len_total - len_first));
	if (!rest)
		return (NULL);
	j = -1;
	while (++len_first < len_total)
		rest[++j] = string[len_first];
	rest[++j] = '\0';
	free(string);
	return (rest);
}
