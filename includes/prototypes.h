/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:24:05 by ajelloul          #+#    #+#             */
/*   Updated: 2025/11/13 10:01:54 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPES_H
# define PROTOTYPES_H

# include "cub3d.h"
# include "structs.h"

int		load_map_data(t_cub *cub, int ac, char **av);
int		open_and_validate_file(char *filepath, int *fd_out);
int		parse_game_settings(t_cub *cub, int fd);
int		configuration_key(t_cub *cub, char *line, int i, int *success);
void	trim_newline(char *str);
int		skip_spaces(char **line);
int		is_whitespace(char c);
bool	is_space(char c);
bool	is_valid_format(char *str);
int		is_line_empty(char *line);
int		is_wall_or_space(char c);
void	trim_trailing_spaces(char *str);
void	free_rbg_values(char **value);
char	*skip_empty_lines(int fd);
int		is_duplicate(t_duplicat_list **list, char *key);
double	deg_to_rad(double degrees);
void	delete_duplicate_list(t_duplicat_list *list);
void	delete_map_rows(t_map_row *map_row);
void	delete_mlx_images(t_cub *cub);
void	delete_textures_paths(t_cub *cub);
int		shutdown_cub(t_cub *cub);
int		parse_map(t_cub *cub, int fd);
int		is_valid_map(t_map_row *map_row);
int		is_tile_enclosed(t_map_row *row, int i);
int		up_valid(t_map_row *up, int pos);
int		down_valid(t_map_row *down, int pos);
int		init_map_from_rows(t_cub *cub, t_map_row *cur_row);
int		player_validator(t_map_row *map_row);
int		is_player_symbol(char c);
int		validate_and_set_player(t_cub *cub);
double	deg_to_rad(double degrees);
void	set_player(t_cub *cub, int x, int y, int angle);
void	display_errors(const char *error_msg);
void	draw_loop(void *param);
void	parse_all_wall_textures(t_cub *cub, char *line, int i, int *success);
char	*extract_texture_path(char *line, int offset);
void	parse_colors(t_cub *cub, char *line, int i, int *succes);
void	free_map_array(t_cub *cub);
void	key_handler(mlx_key_data_t key, void *param);
void	move_player(void *param);
void	clear_image(t_cub *cub);
float	distance(float x, float y);
bool	touch(t_cub *cub, float px, float py);

float	fixed_dist(t_cub *cub, float x1, float y1, float x2, float y2);
void	cast_ray(t_cub *cub, float angle, float *hit_x, float *hit_y, float *perp_dist);

void	draw_textured_slice(t_cub *cub, int screen_x, t_wall_hit *hit, 
			int line_height);

float	calc_tex_x(int side, float hit_x, float hit_y);
void	clamp_pixel_coords(int *pixel_x, int *pixel_y, mlx_texture_t *tex);

#endif
