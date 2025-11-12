/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 11:59:02 by ajelloul          #+#    #+#             */
/*   Updated: 2025/11/12 13:52:21 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	append_row_to_map(t_map_row **map_row, char *line)
{
	t_map_row	*new_row;
	t_map_row	*tail;

	new_row = malloc(sizeof(t_map_row));
	if (!new_row)
		return ;
	new_row->row = line;
	new_row->size = ft_strlen(line);
	new_row->down_row = NULL;
	new_row->up_row = NULL;
	if (!*map_row)
	{
		*map_row = new_row;
		return ;
	}
	tail = *map_row;
	while (tail->down_row)
		tail = tail->down_row;
	tail->down_row = new_row;
	new_row->up_row = tail;
}

/*
	TODO
		Skip empty lines in the top of map
*/

static int	process_map_lines(int fd, t_map_row **rows)
{
	char	*line;

	line = skip_empty_lines(fd);
	while (line)
	{
		trim_newline(line);
		append_row_to_map(rows, line);
		line = get_next_line(fd);
	}
	return (0);
}

int	parse_map(t_cub *cub, int fd)
{
	t_map_row	*map_rows;

	map_rows = NULL;
	process_map_lines(fd, &map_rows);
	if (is_valid_map(map_rows) == 1)
	{
		delete_map_rows(map_rows);
		return (1);
	}
	if (init_map_from_rows(cub, map_rows) == 1)
	{
		delete_map_rows(map_rows);
		return (1);
	}
	delete_map_rows(map_rows);
	return (0);
}
