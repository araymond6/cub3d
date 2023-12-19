/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 11:22:25 by dwawzyni          #+#    #+#             */
/*   Updated: 2023/12/19 10:52:34 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

char	*ft_strtok(char *str, const char *delimiters)
{
	static char	*lasttoken = NULL;
	char		*tokenstart;

	tokenstart = NULL;
	if (str != NULL)
		lasttoken = str;
	else if (lasttoken == NULL)
		return (NULL);
	while (*lasttoken != '\0' && strchr(delimiters, *lasttoken) != NULL)
		lasttoken++;
	if (*lasttoken == '\0')
		while (*lasttoken != '\0' && strchr(delimiters, *lasttoken) != NULL)
			lasttoken++;
	if (*lasttoken == '\0')
		return (lasttoken = NULL);
	tokenstart = lasttoken;
	while (*lasttoken != '\0' && ft_strchr(delimiters, *lasttoken) == NULL)
		lasttoken++;
	if (*lasttoken != '\0')
	{
		*lasttoken = '\0';
		lasttoken++;
	}
	return (tokenstart);
}

int	ft_strcmp(const char *str1, const char *str2)
{
	while (*str1 != '\0' && *str2 != '\0')
	{
		if (*str1 < *str2)
			return (-1);
		else if (*str1 > *str2)
			return (1);
		str1++;
		str2++;
	}
	if (*str1 == '\0' && *str2 == '\0')
		return (0);
	else if (*str1 == '\0')
		return (-1);
	else
		return (1);
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
	int	i;

	i = 0;
	if (map->only_map)
	{
		while (map->only_map[i] != NULL)
		{
			free(map->only_map[i]);
			i++;
		}
	}
	free(map->only_map);
}

void	malloc_error_map(t_map *map, int fd)
{
	if (map->map == NULL)
	{
		close(fd);
		printf("Error\nMemory allocation error\n");
		exit(EXIT_FAILURE);
	}
}
