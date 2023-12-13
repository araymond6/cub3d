#include "../include/cub3D.h"

char	*ft_strtok(char *str, const char *delimiters)
{
	static char *lastToken = NULL;

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

	char *tokenStart = lastToken;
	while (*lastToken != '\0' && ft_strchr(delimiters, *lastToken) == NULL)
		lastToken++;

	if (*lastToken != '\0')
	{
		*lastToken = '\0';
		lastToken++;
	}

	return (tokenStart);
}

int ft_strcmp(const char *str1, const char *str2) 
{
	while (*str1 != '\0' && *str2 != '\0') {
		if (*str1 < *str2) {
			return -1;
		} else if (*str1 > *str2) {
			return 1;
		}
		str1++;
		str2++;
	}

	if (*str1 == '\0' && *str2 == '\0') {
		return 0;
	} else if (*str1 == '\0') {
		return -1;
	} else {
		return 1;
	}
}

int	check_extension(char *path, char *extension)
{
	int i;
	int j;

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

void free_map(t_map *map)
{
	if (map->only_map)
	for (int i = 0; map->only_map[i] != NULL; i++)
	{
		free(map->only_map[i]);
	}
	free(map->only_map);
}

void print_map(t_map *map)
{
	printf("Printing map...\n");

	if (map->only_map == NULL) {
		printf("map->only_map is NULL\n");
		return;
	}
	for (int i = 0; map->only_map[i] != NULL; i++)
	{
		printf("map %i : %s\n", i,  map->only_map[i]);
	}
}
