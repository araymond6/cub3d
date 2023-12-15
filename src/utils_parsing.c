/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwawzyni <dwawzyni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:22:25 by dwawzyni          #+#    #+#             */
/*   Updated: 2023/12/15 11:22:43 by dwawzyni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

char	*ft_strtok(char *str, const char *delimiters)
{
	static char	*lastToken;
	char		*tokenStart;

	lastToken = NULL;
	if (str != NULL)
	{
		lastToken = str;
	}
	else
	{
		if (lastToken == NULL)
		{
			return (NULL);
		}
	}
	while (*lastToken != '\0' && strchr(delimiters, *lastToken) != NULL)
		lastToken++;
	if (*lastToken == '\0')
	{
		lastToken = NULL;
		return (NULL);
	}
	tokenStart = lastToken;
	while (*lastToken != '\0' && ft_strchr(delimiters, *lastToken) == NULL)
		lastToken++;
	if (*lastToken != '\0')
	{
		*lastToken = '\0';
		lastToken++;
	}
	return (tokenStart);
}

int	ft_strcmp(const char *str1, const char *str2)
{
	while (*str1 != '\0' && *str2 != '\0')
	{
		if (*str1 < *str2)
		{
			return (-1);
		}
		else if (*str1 > *str2)
		{
			return (1);
		}
		str1++;
		str2++;
	}
	if (*str1 == '\0' && *str2 == '\0')
	{
		return (0);
	}
	else if (*str1 == '\0')
	{
		return (-1);
	}
	else
	{
		return (1);
	}
}

int	check_extension(char *path, char *extension)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!path || !extension)
		return (-1);
	while (path[i])
		i++;
	while (extension[j])
		j++;
	j--;
	i--;
	while (j >= 0)
	{
		if (path[i] != extension[j])
		{
			return (-1);
		}
		i--;
		j--;
	}
	return (0);
}

void	free_map(t_map *map)
{
	if (map->only_map)
		for (int i = 0; map->only_map[i] != NULL; i++)
		{
			free(map->only_map[i]);
		}
	free(map->only_map);
}
