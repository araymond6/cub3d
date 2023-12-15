#include "../include/cub3D.h"

void	check_map_args(t_map *s_map)
{
	int	fd;
	int	lines_nb;
	int	i;
	int	file_size;

	lines_nb = 0;
	i = 0;
	fd = open(s_map->map_path, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nUnable to open %s\n", s_map->map_path);
		exit(EXIT_FAILURE);
	}
	file_size = count_file_size(fd);
	s_map->map = malloc(sizeof(char *) * (file_size + 1));
	if (s_map->map == NULL)
	{
		close(fd);
		printf("Error\nMemory allocation error\n");
		exit(EXIT_FAILURE);
	}
	close(fd);
	fd = open(s_map->map_path, O_RDONLY);
	s_map->map[i] = get_next_line(fd);
	while (s_map->map[i] && i < file_size)
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

void	set_texture_path(char **dest, char *token, t_map *s_map)
{
	free(*dest);
	*dest = trim_texture_path(s_map, token);

	if (*dest == NULL)
	{
		set_error(s_map, "Unable to get path", MAP_ERROR);
	}
}

void	get_texture_path(t_map *s_map)
{
	int		i;
	char	*line;
	char	*token;

	i = 0;
	while (s_map->map[i])
	{
		line = trim_spaces(s_map->map[i]);
		token = ft_strtok(line, " ");
		while (token != NULL)
		{
			if (ft_strcmp(token, "NO") == 0)
				set_texture_path(&s_map->no_path, ft_strtok(NULL, " "), s_map);
			else if (ft_strcmp(token, "SO") == 0)
				set_texture_path(&s_map->so_path, ft_strtok(NULL, " "), s_map);
			else if (ft_strcmp(token, "WE") == 0)
				set_texture_path(&s_map->we_path, ft_strtok(NULL, " "), s_map);
			else if (ft_strcmp(token, "EA") == 0)
				set_texture_path(&s_map->ea_path, ft_strtok(NULL, " "), s_map);
			else if(ft_strcmp(token,"F") == 0)
				s_map->f_rgb = (ft_strtok(NULL," "));
			else if(ft_strcmp(token,"C") == 0)
				s_map->c_rgb = (ft_strtok(NULL," "));
			else if(s_map->c_rgb != NULL && s_map->f_rgb != NULL && s_map->no_path != NULL && s_map->so_path != NULL 
				&& s_map->we_path != NULL && s_map->ea_path != NULL && s_map->start_map_index == 0)
					s_map->start_map_index = i;
			token = ft_strtok(NULL, " ");
		}
		i++;
	}
	check_params(s_map); // used to check if params exist
}

char	*trim_texture_path(t_map *s_map, char *texture_path)
{
	int		i;
	int		j;
	char	*clean_path;

	i = 0;
	j = 0;
	clean_path = malloc(ft_strlen(texture_path) - i + 1);
	if (clean_path == NULL)
	{
		set_error(s_map, "Memory allocation error", MAP_ERROR);
	}
	while (texture_path[i]) // TODO: check texture path
	{
		clean_path[j] = texture_path[i];
		i++;
		j++;
	}
	clean_path[j] = '\0';
	return (clean_path);
}
