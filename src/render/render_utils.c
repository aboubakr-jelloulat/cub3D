/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 09:59:40 by ajelloul          #+#    #+#             */
/*   Updated: 2025/11/20 10:55:39 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

float	calc_tex_x(int side, float hit_x, float hit_y)
{
	float	wall_coord;

	if (side == 0)
		wall_coord = hit_y - (int)hit_y;
	else
		wall_coord = hit_x - (int)hit_x;
	return (wall_coord);
}

void	clamp_pixel_coords(int *pixel_x, int *pixel_y, mlx_texture_t *tex)
{
	if (*pixel_x < 0)
		*pixel_x = 0;
	if (*pixel_x >= (int)tex->width)
		*pixel_x = (int)tex->width - 1;
	if (*pixel_y < 0)
		*pixel_y = 0;
	if (*pixel_y >= (int)tex->height)
		*pixel_y = (int)tex->height - 1;
}
