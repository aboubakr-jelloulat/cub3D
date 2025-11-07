#include "../../includes/cub3d.h"


static int	validate_textures_and_colors(t_cub *cub)
{

	if (cub->list_status.is_wrong_txtr_extension)
		return (display_errors("Wrong texture extension: must be [.png]\n"), 1);
	if (cub->list_status.is_duplicate_key)
		return (display_errors("Error: Duplicate components\n"), 1);
	if (cub->list_status.invalid_key)
		return (display_errors("Error: Invalid key\n"), 1);
	return (0);
}


/*

	read until map = read textures path and colors only untl succes = 6

	printf("%s", line);
	printf("%d", offset);
*/

/*

	TODO:
		parse wall and save path
		parse color and save the floor and ceil

*/



static int	read_until_complete(t_cub *cub, int fd, int *count)
{
	char	*line;
	int		offset;

	line = get_next_line(fd);
	while (line)
	{
		trim_newline(line);
		offset = skip_spaces(&line);
		if (!configuration_key(cub, line, offset, count))
		{
			if (line)
				free(line);
			break ;
		}
		if (line)
			free(line);
		if (*count == 6)
			break ;
		line = get_next_line(fd);
	}
	return (0);
}

int	parse_game_settings(t_cub *cub, int fd)
{
	int	success_count;

	success_count = 0;
	read_until_complete(cub, fd, &success_count);
	delete_duplicate_list(cub->duplicate_list);
	cub->duplicate_list = NULL;
	return (validate_textures_and_colors(cub));
}
