/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migupere <migupere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:32:35 by migupere          #+#    #+#             */
/*   Updated: 2024/05/08 15:09:18 by migupere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	expand(char *key, int i, int j, char **line)
{
    char	*tmp;
    char	*tmp2;

    tmp = ft_substr(*line, 0, i);
    if (!tmp)
        return (-1);
    tmp2 = ft_substr(*line, j, ft_strlen(*line) - j + 1);
    if (!tmp2)
    {
        free(tmp);
        return (-1);
    }
    free(*line);
    *line = ft_strjoin(tmp, key);
    free(tmp);
    if (!*line)
    {
        free(tmp2);
        return (-1);
    }
    tmp = *line;
    *line = ft_strjoin(*line, tmp2);
    free(tmp);
    free(tmp2);
    if (!*line)
        return (-1);
    return (0);
}

int	expand_free(char *key, int i, int j, char **line)
{
    int ret = expand(key, i, j, line);
    free(key);
    return ret;
}
