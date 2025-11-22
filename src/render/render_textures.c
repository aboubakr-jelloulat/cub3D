/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 09:56:11 by ajelloul          #+#    #+#             */
/*   Updated: 2025/11/22 15:39:04 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static mlx_texture_t	*get_wall_texture(t_cub *cub, int side,
	float hit_x, float hit_y)
{
	if (side == 0)
	{
		if (cub->player.x < (hit_x * BLOCK))
			return (cub->textures.mlx_east);
		else
			return (cub->textures.mlx_west);
	}
	else
	{
		if (cub->player.y < (hit_y * BLOCK))
			return (cub->textures.mlx_south);
		else
			return (cub->textures.mlx_north);
	}
}

static uint32_t	sample_texture(mlx_texture_t *tex, float tex_x, float tex_y)
{
	int		pixel_x;
	int		pixel_y;
	int		index;
	uint8_t	*pixels;
	uint8_t	rgba[4];

	pixel_x = (int)(tex_x * (int)(tex->width - 1));
	pixel_y = (int)(tex_y * (int)(tex->height - 1));
	clamp_pixel_coords(&pixel_x, &pixel_y, tex);
	pixels = (uint8_t *)tex->pixels;
	index = (pixel_y * (int)tex->width + pixel_x) * (int)tex->bytes_per_pixel;
	rgba[0] = pixels[index];
	rgba[1] = pixels[index + 1];
	rgba[2] = pixels[index + 2];
	rgba[3] = pixels[index + 3];
	return ((rgba[0] << 24) | (rgba[1] << 16) | (rgba[2] << 8) | rgba[3]);
}

static void	init_draw_params(t_wall_hit *hit, int line_height,
	t_draw_params *params)
{
	params->texture = get_wall_texture(hit->cub, hit->side,
			hit->hit_x, hit->hit_y);
	params->draw_start = (HEIGHT - line_height) / 2;
	params->draw_end = params->draw_start + line_height;
	if (params->draw_start < 0)
		params->draw_start = 0;
	if (params->draw_end >= HEIGHT)
		params->draw_end = HEIGHT - 1;
	params->tex_x = calc_tex_x(hit->side, hit->hit_x, hit->hit_y);
	params->step = (double)(1.0 / line_height);
	params->tex_y = (double)(params->draw_start - (HEIGHT - line_height) / 2)
		* params->step;
}

void	draw_textured_slice(t_cub *cub, int screen_x,
	t_wall_hit *hit, int line_height)
{
	t_draw_params	params;
	uint32_t		color;
	int				y;

	hit->cub = cub;
	init_draw_params(hit, line_height, &params);
	y = params.draw_start;
	while (y < params.draw_end)
	{
		color = sample_texture(params.texture, params.tex_x, params.tex_y);
		mlx_put_pixel(cub->image, screen_x, y, color);
		y++;
		params.tex_y += params.step;
	}
}
