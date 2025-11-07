/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_validator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 11:43:14 by ajelloul          #+#    #+#             */
/*   Updated: 2025/11/04 10:52:24 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"



int	is_player_symbol(char c)
{
	return (c == 'N' || c == 'E' || c == 'S' || c == 'W');
}

// // Check if player spawn position is safe (surrounded by valid tiles)
// static int	is_player_spawn_safe(t_map_row *row, int pos)
// {
// 	// Check left side
// 	if (pos > 0 && row->row[pos - 1] == ' ')
// 		return (0);
// 	// Check right side
// 	if (row->row[pos + 1] == '\0' || row->row[pos + 1] == ' ')
// 		return (0);
// 	// Check up
// 	if (!up_valid(row->up_row, pos))
// 		return (0);
// 	// Check down
// 	if (!down_valid(row->down_row, pos))
// 		return (0);
// 	return (1);
// }

int	player_validator(t_map_row *map_row)
{
	t_map_row	*current;
	int			player_count;
	int			pos;

	player_count = 0;
	current = map_row;
	while (current)
	{
		pos = 0;
		while (current->row[pos])
		{
			if (is_player_symbol(current->row[pos]))
			{
				player_count++;
				if (player_count > 1)
					return (display_errors("Multiple player spawn points found"), 1);
			}
			pos++;
		}
		current = current->down_row;
	}
	if (player_count == 0)
		return (display_errors("No player spawn point found"), 1);
	return (0);
}


// int	is_player_symbol(char c)
// {
// 	return (c == 'N' || c == 'E' || c == 'S' || c == 'W');
// }


// static int	is_player_spawn_safe(t_map_row *row, int pos)
// {
// 	if (!up_valid(row->up_row, pos))
// 		return (0);
// 	if (!down_valid(row->down_row, pos))
// 		return (0);
// 	if (is_whitespace(row->row[pos + 1]))
// 		return (0);
// 	if (pos > 0 && is_whitespace(row->row[pos - 1]))
// 		return (0);
// 	return (1);
// }

// static int	handle_player_found(int *count, t_map_row *row, int pos)
// {
// 	(*count)++;
// 	if (*count > 1)
// 		return (display_errors("Player point is invalid"), 1);
// 	if (!is_player_spawn_safe(row, pos))
// 		return (display_errors("Player point is invalid"), 1);
// 	return (0);
// }

// static int	scan_row_for_player(t_map_row *row, int *total_count)
// {
// 	int	idx;

// 	idx = 0;
// 	while (row->row[idx])
// 	{
// 		if (is_player_symbol(row->row[idx]))
// 		{
// 			if (handle_player_found(total_count, row, idx))
// 				return (1);
// 		}
// 		idx++;
// 	}
// 	return (0);
// }

// int	player_validator(t_map_row *map_row)
// {
// 	t_map_row	*current;
// 	int			player_count;

// 	current = map_row;
// 	player_count = 0;
// 	while (current)
// 	{
// 		if (scan_row_for_player(current, &player_count))
// 			return (1);
// 		current = current->down_row;
// 	}
// 	if (player_count == 0)
// 		return (display_errors("No player spawn point in map"), 1);
// 	return (EXIT_SUCCESS);
// }

