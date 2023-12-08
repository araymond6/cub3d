#include "../include/cub.h"
#define MAX_LINES 100

void	check_map_args(t_map *s_map)
{
	int	fd;
	int	lines_nb;
	int	i;

	lines_nb = 0;
	i = 0;
	fd = open(s_map->map_path, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	s_map->map = malloc(sizeof(char *) * MAX_LINES);
	if (s_map->map == NULL)
	{
		perror("Memory allocation error");
		exit(EXIT_FAILURE);
	}
	s_map->map[i] = get_next_line(fd);
	while (s_map->map[i] && i < MAX_LINES - 1)
	{
		s_map->map[++i] = get_next_line(fd);
		lines_nb++;
	}
	close(fd);
}
char	*trim_spaces(char *str)
{
	char	*end;

	while (isspace(*str))
	{
		str++;
	}
	end = str + strlen(str) - 1;
	while (end > str && isspace(*end))
	{
		end--;
	}
	*(end + 1) = '\0';
	return (str);
}

void set_texture_path(char **dest, char *token, char *path_name, t_map *s_map)
{
    free(*dest);
    *dest = trim_texture_path(token);

    if (*dest == NULL)
    {
        perror("Error getting path");
        exit(EXIT_FAILURE);
    }
}

void get_texture_path(t_map *s_map)
{
    int i = 0;
	s_map->EA_path = NULL;
	s_map->NO_path = NULL;
	s_map->WE_path = NULL;
	s_map->SO_path = NULL;
	s_map->start_map_index = 0;
    while (s_map->map[i])
    {
        char *line = trim_spaces(s_map->map[i]);
        char *token = ft_strtok(line, " ");

        while (token != NULL)
        {
            if (ft_strcmp(token, "NO") == 0)
                set_texture_path(&s_map->NO_path, ft_strtok(NULL, " "), "NO", s_map);
            else if (ft_strcmp(token, "SO") == 0)
                set_texture_path(&s_map->SO_path, ft_strtok(NULL, " "), "SO", s_map);
            else if (ft_strcmp(token, "WE") == 0)
                set_texture_path(&s_map->WE_path, ft_strtok(NULL, " "), "WE", s_map);
            else if (ft_strcmp(token, "EA") == 0)
                set_texture_path(&s_map->EA_path, ft_strtok(NULL, " "), "EA", s_map);
			else if(ft_strcmp(token,"F") == 0)
				s_map->f_rgb = (ft_strtok(NULL," "));
			else if(ft_strcmp(token,"C") == 0)
				s_map->c_rgb = (ft_strtok(NULL," "));
			else if(s_map->c_rgb != NULL && s_map->f_rgb != NULL && s_map->NO_path != NULL && s_map->SO_path != NULL 
				&& s_map->WE_path != NULL && s_map->EA_path != NULL && s_map->start_map_index == 0)
					s_map->start_map_index = i;
            token = ft_strtok(NULL, " ");
        }
        i++;
    }
}


char	*trim_texture_path(char *texture_path)
{
	int i = 0;
	int j = 0;

	while (texture_path[i] != '/' && texture_path[i] != '\0')
		i++;
	if (texture_path[i] == '\0')
	{
		perror("Dot not found in texture path");
		return (NULL);
	}
	char *clean_path = malloc(ft_strlen(texture_path) - i + 1);

	if (clean_path == NULL)
	{
		perror("Memory allocation error in trim_texture_path");
		exit(EXIT_FAILURE);
	}
	while (texture_path[i])
	{
		clean_path[j] = texture_path[i];
		i++;
		j++;
	}
	clean_path[j] = '\0';
	return (clean_path);
}
