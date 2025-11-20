/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krai <ael-krai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 19:02:23 by ael-krai          #+#    #+#             */
/*   Updated: 2025/11/20 11:40:32 by ael-krai         ###   ########.fr       */
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

void draw_loop(void *param)
{
	t_cub		*cub;
	float		ray_angle;
	float		angle_step;
	int			i;
	float		hit_x;
	float		hit_y;
	float		perp_dist;
	int			line_height;
	t_wall_hit	wall_hit;

	cub = (t_cub *)param;
	move_player(cub);
	draw_floor_ceiling(cub);
	cub->player.dist_proj_plane = (WIDTH / 2.0f) / tanf(FOV / 2.0f);
	angle_step = FOV / (float)WIDTH;
	ray_angle = cub->player.angle - FOV / 2.0f;
	i = 0;
	while (i < WIDTH)
	{
		cast_ray(cub, ray_angle, &hit_x, &hit_y, &perp_dist);
		perp_dist = perp_dist * cosf(ray_angle - cub->player.angle);
		wall_hit.hit_x = hit_x / (float)BLOCK; // Prepare wall hit data
		wall_hit.hit_y = hit_y / (float)BLOCK;
		wall_hit.perp_dist = perp_dist;
		wall_hit.side = cub->dda->side;  // from your DDA loop
		line_height = (int)((float)BLOCK / perp_dist * cub->player.dist_proj_plane);
		draw_textured_slice(cub, i, &wall_hit, line_height);
		ray_angle += angle_step;
		i++;
	}
}
