/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pevieira <pevieira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:02:16 by pevieira          #+#    #+#             */
/*   Updated: 2023/11/21 19:10:05 by pevieira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_ws(char const *str, char c)
{
	size_t	words;

	words = 0;
	while (*str)
	{
		if (*str != c)
		{
			words++;
			while (*str != c && *str != '\0')
				str++;
		}
		else
			str++;
	}
	return (words);
}

static char	*ft_word(char const *s, char c)
{
	size_t	i;
	char	*word;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	word = (char *) malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**words_splitted;
	size_t	i;

	i = 0;
	words_splitted = (char **) malloc(sizeof(char *) * (count_ws(s, c) + 1));
	if (!words_splitted || !s)
		return (NULL);
	while (*s != '\0')
	{
		if (*s != c)
		{
			words_splitted[i] = ft_word(s, c);
			while (*s && *s != c)
				s++;
			i++;
		}
		else
			s++;
	}
	words_splitted[i] = NULL;
	return (words_splitted);
}
