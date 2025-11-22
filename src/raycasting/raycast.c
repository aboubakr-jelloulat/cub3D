/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krai <ael-krai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 16:19:24 by ael-krai          #+#    #+#             */
/*   Updated: 2025/11/20 11:41:20 by ael-krai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ray_direction(t_cub *cub, float angle, t_dda *dda)
{
	dda->pos_x = cub->player.x / (float)BLOCK;
	dda->pos_y = cub->player.y / (float)BLOCK;
	dda->ray_dir_x = cosf(angle);
	dda->ray_dir_y = sinf(angle);
	dda->map_x = (int)dda->pos_x;
	dda->map_y = (int)dda->pos_y;
	dda->delta_dist_x = fabsf(1.0f / dda->ray_dir_x);
	dda->delta_dist_y = fabsf(1.0f / dda->ray_dir_y);
}

void	step_and_side_dist(t_dda *dda)
{
	if (dda->ray_dir_x < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = (dda->pos_x - dda->map_x) * dda->delta_dist_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = (dda->map_x + 1 - dda->pos_x) * dda->delta_dist_x;
	}
	if (dda->ray_dir_y < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = (dda->pos_y - dda->map_y) * dda->delta_dist_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = (dda->map_y + 1 - dda->pos_y) * dda->delta_dist_y;
	}
}

int	dda_loop(t_cub *cub, t_dda *dda, int step, int max_steps)
{
	max_steps = (int)sqrt(cub->map.width * cub->map.width
			+ cub->map.height * cub->map.height) + 5;
	while (step < max_steps)
	{
		if (dda->side_dist_x < dda->side_dist_y)
		{
			dda->side_dist_x += dda->delta_dist_x;
			dda->map_x += dda->step_x;
			dda->side = 0;
		}
		else
		{
			dda->side_dist_y += dda->delta_dist_y;
			dda->map_y += dda->step_y;
			dda->side = 1;
		}
		if (dda->map_y < 0 || dda->map_y >= cub->map.height || 
			dda->map_x < 0 || dda->map_x >= cub->map.width)
			return (0);
		if (cub->map.map[dda->map_y][dda->map_x] == '1')
			return (1);
		step++;
	}
	return (0);
}

void	cast_ray(t_cub *cub, float *hit_x, float *hit_y, float *perp_dist)
{
	t_dda	dda;

	ray_direction(cub, cub->ray_angle, &dda);
	step_and_side_dist(&dda);
	dda_loop(cub, &dda, 0, 0);
	if (!cub->dda)
		cub->dda = malloc(sizeof(t_dda));
	cub->dda->side = dda.side;
	if (dda.side == 0)
		*perp_dist = (dda.side_dist_x - dda.delta_dist_x) * BLOCK;
	else
		*perp_dist = (dda.side_dist_y - dda.delta_dist_y) * BLOCK;
	if (*perp_dist < 0.1f)
		*perp_dist = 0.1f;
	*hit_x = cub->player.x + dda.ray_dir_x * (*perp_dist);
	*hit_y = cub->player.y + dda.ray_dir_y * (*perp_dist);
}
