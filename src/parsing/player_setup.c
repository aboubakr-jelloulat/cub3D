/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 12:08:25 by ajelloul          #+#    #+#             */
/*   Updated: 2025/11/05 15:43:32 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"


// static int	convert_direction(char c)
// {
// 	if (c == 'N')
// 		return (270);
// 	if (c == 'S')
// 		return (90);
// 	if (c == 'E')
// 		return (0);
// 	if (c == 'W')
// 		return (180);
// 	return (-1);
// }

// static int	process_player_position(t_cub *cub, int x, int y)
// {
// 	char	tile;
// 	int		direction;

// 	tile = cub->map.map[y][x];
// 	if (is_player_symbol(tile))
// 	{
// 		direction = convert_direction(tile);
// 		set_player(cub, x, y, direction);
// 		return (1);
// 	}
// 	return (0);
// }

// static int	scan_map_for_player(t_cub *cub)
// {
// 	int	x;
// 	int	y;

// 	y = 0;
// 	while (y < cub->map.height)
// 	{
// 		x = 0;
// 		while (x < cub->map.width)
// 		{
// 			if (process_player_position(cub, x, y))
// 				return (EXIT_SUCCESS);
// 			x++;
// 		}
// 		y++;
// 	}
// 	return (EXIT_FAILURE);
// }

// int	find_player_start(t_cub *cub)
// {
// 	if (!cub || !cub->map.map)
// 		return (EXIT_FAILURE);
// 	return (scan_map_for_player(cub));
// }


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

// player  ***** 
// Find and set player start position and direction
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
