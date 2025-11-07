/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 09:40:05 by ajelloul          #+#    #+#             */
/*   Updated: 2025/11/06 10:22:01 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "cub3d.h"

typedef struct s_dda
{
	float	pos_x;
	float	pos_y;
	float	ray_dir_x;
	float	ray_dir_y;
	float	delta_dist_x;
	float	delta_dist_y;
	float	side_dist_x;
	float	side_dist_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
}	t_dda;

typedef struct s_map_row
{
	char				*row;
	int					size;
	struct s_map_row	*up_row;
	struct s_map_row	*down_row;
}	t_map_row;

typedef struct s_player
{
	int		x;
	int		y;
	float	angle;
	float	radius;
	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;
	bool	left_rotate;
	bool	right_rotate;
	float	dist_proj_plane;
}	t_player;

typedef struct s_map
{
	char	**map;
	int		width;
	int		height;
}	t_map;

typedef struct s_texture
{
	mlx_texture_t	*mlx_north;
	mlx_texture_t	*mlx_south;
	mlx_texture_t	*mlx_west;
	mlx_texture_t	*mlx_east;
}	t_texture;

typedef struct s_list_status
{
	bool	is_duplicate_key;
	bool	is_wrong_txtr_extension;
	int		floor_color;
	int		ceiling_color;
	bool	invalid_key;
}	t_list_status;

typedef struct s_duplicat_list
{
	char					*key;
	struct s_duplicat_list	*next;
}	t_duplicat_list;

typedef struct s_key_matcher
{
	char	*pattern;
	int		pattern_len;
}	t_key_matcher;


// render 

typedef struct s_wall_hit
{
	int		side;       // 0 = vertical (NS), 1 = horizontal (EW)
	float	hit_x;      // exact hit point x
	float	hit_y;      // exact hit point y
	float	perp_dist;  // perpendicular distance
}	t_wall_hit;

typedef struct s_cub
{
	char			*no_texture_path;
	char			*so_texture_path;
	char			*we_texture_path;
	char			*ea_texture_path;
	t_duplicat_list	*duplicate_list;
	t_list_status	list_status;
	t_texture		textures;
	mlx_image_t		*image;
	t_player		player;
	mlx_t			*mlx;
	t_dda			*dda;
	t_map			map;
	bool			floor_color_set;
	bool			ceiling_color_set;
}	t_cub;

#endif
