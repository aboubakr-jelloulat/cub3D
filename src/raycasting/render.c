/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 18:55:37 by ael-krai          #+#    #+#             */
/*   Updated: 2025/11/06 12:59:18 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

float distance(float x, float y)
{
    return (sqrt(x * x + y * y));
}

float fixed_dist(t_cub *cub, float x1, float y1, float x2, float y2)

{
    float delta_x;
    float delta_y;
    float fix_dist;
    float angle;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	angle = atan2(delta_y, delta_x) - cub->player.angle;
	fix_dist = distance(delta_x, delta_y) * cos(angle);
    return (fix_dist);
}

bool touch(t_cub *cub, float px, float py)
{
    int x;
    int y;

    x = px / BLOCK;
    y = py / BLOCK;
    if (y < 0 || y >= cub->map.height || x < 0 || x >= cub->map.width)
        return (true);
    if (cub->map.map[y][x] == '1')
        return (true);
    return (false);
}

void clear_image(t_cub *cub)
{
    int x;
    int y;
	(void)cub;

    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            mlx_put_pixel(cub->image, x, y, 0x000000);
            x++;
        }
        y++;
    }
}
