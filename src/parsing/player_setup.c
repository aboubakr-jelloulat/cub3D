/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 12:08:25 by ajelloul          #+#    #+#             */
/*   Updated: 2025/11/12 13:57:11 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Convert player direction character to angle in degrees
double	deg_to_rad(double degrees)
{
	return (degrees * (M_PI / 180.0));
}

void	set_player(t_cub *cub, int x, int y, int angle)
{
	cub->player.x = x;
	cub->player.y = y;
	cub->player.radius = deg_to_rad(angle);
}

static int	get_player_angle(char direction)
{
	if (direction == 'N')
		return (270);
	if (direction == 'S')
		return (90);
	if (direction == 'E')
		return (0);
	if (direction == 'W')
		return (180);
	return (-1);
}

int	validate_and_set_player(t_cub *cub)
{
	int		x;
	int		y;
	char	tile;

	if (!cub || !cub->map.map)
		return (1);
	y = 0;
	while (y < cub->map.height)
	{
		x = 0;
		while (x < cub->map.width)
		{
			tile = cub->map.map[y][x];
			if (is_player_symbol(tile))
			{
				set_player(cub, x, y, get_player_angle(tile));
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

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
					return (display_errors
						("Multiple player spawn points found"), 1);
			}
			pos++;
		}
		current = current->down_row;
	}
	if (player_count == 0)
		return (display_errors("No player spawn point found"), 1);
	return (0);
}
