/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_map_tile_enclosed.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:47:54 by ajelloul          #+#    #+#             */
/*   Updated: 2025/11/12 13:47:58 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*It checks: “Is this tile a place the player can walk or stand on?”*/
static int	is_playable_tile(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

/*
	CASE 1 :
			*First Lines : 11111111111111E11
	CASE 2 :
			*Sizes : 
					111111111
					111111111111E11
	CASE 3 :

			*UP Top:
					111111111
					111 11111
					111E11111

*/

static int	is_neighbor_safe(t_map_row *neighbor, int pos)
{
	if (!neighbor)
		return (0);
	if (pos >= neighbor->size)
		return (0);
	if (neighbor->row[pos] == ' ')
		return (0);
	return (1);
}

int	up_valid(t_map_row *up, int pos)
{
	return (is_neighbor_safe(up, pos));
}

int	down_valid(t_map_row *down, int pos)
{
	return (is_neighbor_safe(down, pos));
}

// Main function: There is no hole in the walls  the map is completely closed

/*
	Fokax katkoun machi safe :
		111   ← up_row
		10001 ← current row

	+
	NOT SAFE (space)
		1 111 ← up_row
		10001 ← current row

*/

/*

	CASE 1 :
		If the next character doesn’t exist
		1100110  -> next is space or '\0'
		or 
		111111111
		11E 11111
		111111111  => space found 

	CASE 2 : 
		UP & DOWN

	CASE 3 :
			111111111
			11 E11111
			111111111

*/
int	is_tile_enclosed(t_map_row *row, int pos)
{
	char	current;

	current = row->row[pos];
	if (is_playable_tile(current))
	{
		if (row->row[pos + 1] == '\0' || row->row[pos + 1] == ' ')
			return (1);
		if (!up_valid(row->up_row, pos))
			return (1);
		if (!down_valid(row->down_row, pos))
			return (1);
	}
	else if (current == ' ' && is_playable_tile(row->row[pos + 1]))
		return (1);
	return (0);
}
