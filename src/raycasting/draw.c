/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 19:02:23 by ael-krai          #+#    #+#             */
/*   Updated: 2025/11/22 11:57:56 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_floor_ceiling(t_cub *cub)
{
    int x;
    int y;

    y = 0;
    while (y < HEIGHT / 2)
    {
        x = 0;
        while (x < WIDTH)
        {
            mlx_put_pixel(cub->image, x, y, cub->list_status.ceiling_color);
            x++;
        }
        y++;
    }
    y = HEIGHT / 2;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            mlx_put_pixel(cub->image, x, y, cub->list_status.floor_color);
            x++;
        }
        y++;
    }
}

void	init_wall_hit(t_wall_hit *wall_hit, float hit_x, float hit_y,
	float perp_dist)
{
	wall_hit->hit_x = hit_x / (float)BLOCK;
	wall_hit->hit_y = hit_y / (float)BLOCK;
	wall_hit->perp_dist = perp_dist;
	wall_hit->side = wall_hit->cub->dda->side;
}

/*
	hit[0] = hit_x
	hit[1] = hit_y
	hit[2] = perp_dist
	line_height = (int)((float)BLOCK / hit[2] * cub->player.dist_proj_plane);
	
*/
void	draw_loop(void *param)
{
	t_cub		*cub;
	int			i;
	float		ray_angle;
	float		hit[3];
	t_wall_hit	wall_hit;

	cub = (t_cub *)param;
	move_player(cub);
	draw_floor_ceiling(cub);
	cub->player.dist_proj_plane = (WIDTH / 2.0f) / tanf(FOV / 2.0f);
	ray_angle = cub->player.angle - FOV / 2.0f;
	wall_hit.cub = cub;
	i = -1;
	while (++i < WIDTH)
	{
		cast_ray(cub, ray_angle, &hit[0], &hit[1], &hit[2]);
		hit[2] *= cosf(ray_angle - cub->player.angle);
		init_wall_hit(&wall_hit, hit[0], hit[1], hit[2]);
		draw_textured_slice(cub, i, &wall_hit,
			(int)((float)BLOCK / hit[2] * cub->player.dist_proj_plane));
		ray_angle += FOV / (float)WIDTH;
	}
}
