/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 11:22:47 by ajelloul          #+#    #+#             */
/*   Updated: 2025/11/19 11:10:33 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_valid_map_char(char c)
{
	if (c == '1' || c == '0')
		return (1);
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	if (is_whitespace(c))
		return (1);
	display_errors("Unknown character detected");
	return (0);
}

/*
	if (row->row[pos] == '1') ????  If the tile is a wall
		there nothing wrong bla matchiki 
*/

int	scan_row_positions(t_map_row *row)
{
	int		pos;
	char	current;

	pos = 0;
	while (row->row[pos])
	{
		current = row->row[pos];
		if (!is_valid_map_char(current))
			return (1);
		if (current == '1')
		{
			pos++;
			continue ;
		}
		if (is_tile_enclosed(row, pos))
		{
			display_errors("Map not properly enclosed");
			return (1);
		}
		pos++;
	}
	return (0);
}

static int	validate_row_start(t_map_row *row)
{
	int	start;

	start = skip_spaces(&row->row);
	if (row->row[start] != '1')
	{
		display_errors("Invalid Map - row doesn't start with a wall");
		return (1);
	}
	return (0);
}

int	is_valid_map(t_map_row *map_row)
{
	t_map_row	*current;

	current = map_row;
	while (current)
	{
		if (validate_row_start(current))
			return (1);
		if (scan_row_positions(current))
			return (1);
		current = current->down_row;
	}
	return (player_validator(map_row));
}
