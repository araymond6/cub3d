#include "../include/cub3D.h"
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
		printf("Error\nUnable to open %s\n", s_map->map_path);
		exit(EXIT_FAILURE);
	}
	s_map->map = malloc(sizeof(char *) * MAX_LINES);
	if (s_map->map == NULL)
	{
		printf("Error\nMemory allocation error\n");
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

	while (ft_isspace(*str))
	{
		str++;
	}
	end = str + ft_strlen(str) - 1;
	while (end > str && ft_isspace(*end))
	{
		end--;
	}
	*(end + 1) = '\0';
	return (str);
}

void set_texture_path(char **dest, char *token, t_map *s_map)
{
	free(*dest);
	*dest = trim_texture_path(s_map, token);

	if (*dest == NULL)
	{
		set_error(s_map, "Unable to get path", MAP_ERROR);
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
				set_texture_path(&s_map->NO_path, ft_strtok(NULL, " "), s_map);
			else if (ft_strcmp(token, "SO") == 0)
				set_texture_path(&s_map->SO_path, ft_strtok(NULL, " "), s_map);
			else if (ft_strcmp(token, "WE") == 0)
				set_texture_path(&s_map->WE_path, ft_strtok(NULL, " "), s_map);
			else if (ft_strcmp(token, "EA") == 0)
				set_texture_path(&s_map->EA_path, ft_strtok(NULL, " "), s_map);
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


char	*trim_texture_path(t_map *s_map, char *texture_path)
{
	int i = 0;
	int j = 0;
	char *clean_path;
	
	clean_path = malloc(ft_strlen(texture_path) - i + 1);
	if (clean_path == NULL)
	{
		set_error(s_map, "Memory allocation error", MAP_ERROR);
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
