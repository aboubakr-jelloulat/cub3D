#include "../../includes/cub3d.h"

// Get the correct texture based on wall side and direction
static mlx_texture_t	*get_wall_texture(t_cub *cub, int side, float hit_x, float hit_y)
{
	if (side == 0)  // vertical wall (North-South)
	{
		if (cub->player.x < (hit_x * BLOCK))
			return (cub->textures.mlx_east);
		else
			return (cub->textures.mlx_west);
	}
	else  // horizontal wall (East-West)
	{
		if (cub->player.y < (hit_y * BLOCK))
			return (cub->textures.mlx_south);
		else
			return (cub->textures.mlx_north);
	}
}

// Calculate texture X coordinate (0.0 to 1.0 along wall)
static float	calc_tex_x(int side, float hit_x, float hit_y)
{
	float	wall_coord;

	if (side == 0)  // vertical wall
		wall_coord = hit_y - (int)hit_y;
	else  // horizontal wall
		wall_coord = hit_x - (int)hit_x;
	
	if (wall_coord < 0.0f)
		wall_coord += 1.0f;
	
	return (wall_coord);
}

// Read pixel from texture using normalized coordinates
// FIXED: Proper byte handling for RGBA format
static uint32_t	sample_texture(mlx_texture_t *tex, float tex_x, float tex_y)
{
	int		pixel_x;
	int		pixel_y;
	int		index;
	uint8_t	*pixels;
	uint8_t	r, g, b, a;

	if (!tex)
		return (0xFF0000FF);  // Red with full alpha
	
	pixel_x = (int)(tex_x * (int)(tex->width - 1));
	pixel_y = (int)(tex_y * (int)(tex->height - 1));
	
	// Clamp to texture bounds
	if (pixel_x < 0)
		pixel_x = 0;
	if (pixel_x >= (int)tex->width)
		pixel_x = (int)tex->width - 1;
	if (pixel_y < 0)
		pixel_y = 0;
	if (pixel_y >= (int)tex->height)
		pixel_y = (int)tex->height - 1;
	
	pixels = (uint8_t *)tex->pixels;
	index = (pixel_y * (int)tex->width + pixel_x) * (int)tex->bytes_per_pixel;
	
	// Read RGBA bytes individually (handles endianness properly)
	r = pixels[index];
	g = pixels[index + 1];
	b = pixels[index + 2];
	a = pixels[index + 3];
	
	// Return in correct format: RGBA
	return ((uint32_t)r << 24) | ((uint32_t)g << 16) | ((uint32_t)b << 8) | (uint32_t)a;
}

// Draw one vertical wall slice with texture
void	draw_textured_slice(t_cub *cub, int screen_x, t_wall_hit *hit, int line_height)
{
	float		tex_x;
	double		tex_y;
	double		step;
	int			draw_start;
	int			draw_end;
	int			y;
	mlx_texture_t	*texture;
	uint32_t	color;

	// Get correct texture for this wall
	texture = get_wall_texture(cub, hit->side, hit->hit_x, hit->hit_y);
	
	// Calculate texture X (same for entire column)
	tex_x = calc_tex_x(hit->side, hit->hit_x, hit->hit_y);
	
	// Calculate draw bounds
	draw_start = (HEIGHT - line_height) / 2;
	draw_end = draw_start + line_height;
	
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	
	// How much texture moves per screen pixel
	step = 1.0 / line_height;
	
	// Starting texture Y
	tex_y = (float)(draw_start - (HEIGHT - line_height) / 2) * step;
	
	// Draw vertical stripe
	y = draw_start;
	while (y < draw_end)
	{
		color = sample_texture(texture, tex_x, tex_y);
		mlx_put_pixel(cub->image, screen_x, y, color);
		y++;
		tex_y += step;
	}
}
