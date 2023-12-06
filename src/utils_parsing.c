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
