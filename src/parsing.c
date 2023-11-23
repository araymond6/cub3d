#include "../include/cub.h"
int	linecount(t_map *s_map)
{
	int		fd;
	int		i;
	char	buf;
	int		counter;

	counter = 0;
	fd = open(s_map->map_path, O_RDONLY);
	i = 1;
	while (1)
	{
		i = read(fd, &buf, 1);
		if (i == 0)
			break ;
		if (i < 0)
			return (-1);
		if (buf == '\n')
			counter++;
	}
	close(fd);
	return (counter + 1);
}
void check_map_args(t_map *s_map)
{
    int fd;
    int lines_nb = 0;
    int i = 0;

    fd = open(s_map->map_path, O_RDONLY);

    s_map->map = ft_gc_malloc(sizeof(char *) * linecount(s_map))+1;
    s_map->map[i] = get_next_line(fd);
    while (s_map->map[i])
	{
		s_map->map[++i] = get_next_line(fd);
		lines_nb++;
	}
	close(fd);
}

int map_size(t_map s_map)
{

}