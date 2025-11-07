#ifndef PROTOTYPES_H
# define PROTOTYPES_H

# include "cub3d.h"
# include "structs.h"


int	load_map_data(t_cub *cub, int ac, char **av);
int	open_and_validate_file(char *filepath, int *fd_out);
int	parse_game_settings(t_cub *cub, int fd);


// config key 
int	configuration_key(t_cub *cub, char *line, int i, int *success);


// utils 
void	trim_newline(char *str);
int		skip_spaces(char **line);
int		is_whitespace(char c);
bool	is_space(char c);
int		is_empty_line(char *line);
int	is_wall_or_space(char c);
void	trim_trailing_spaces(char *str);
void	free_rbg_values(char **value);
char	*skip_empty_lines(int fd);
int	is_duplicate(t_duplicat_list **list, char *key);



double	deg_to_rad(double degrees);



// garbage collection
void	cleanup_line_buffer(char *line);
void	delete_duplicate_list(t_duplicat_list *list);
void	delete_map_rows(t_map_row *map_row);
void	delete_mlx_images(t_cub *cub);
void	delete_textures_paths(t_cub *cub);
void	delete_map(t_cub *cub);
int	shutdown_cub(t_cub *cub);



// validate_textures_and_colors
int	check_colors_config(t_cub *cub);
int	check_extension_errors(t_cub *cub);
int	check_duplicate_keys(t_cub *cub);
int	validate_all_textures(t_cub *cub);


// parse map
int	parse_map(t_cub *cub, int fd);

// is valid map 
int	is_valid_map(t_map_row *map_row);
int	validate_character(t_map_row *row, int pos);

int	is_tile_enclosed(t_map_row *row, int i);

int	up_valid(t_map_row *up, int pos);
int	down_valid(t_map_row *down, int pos);


// init map
int	init_map_from_rows(t_cub *cub, t_map_row *cur_row);


// player_validator
int	player_validator(t_map_row *map_row);


// player_validator utils
int	is_player_symbol(char c);

// player setup
int		validate_and_set_player(t_cub *cub);
double	deg_to_rad(double degrees);
void	set_player(t_cub *cub, int x, int y, int angle);




void	display_errors(const char *error_msg);




/*     Randring  / Recast      */

// draw
void    draw_line(t_cub *cub, float start_x, int i);
void draw_loop(void *param);

// hooks
void key_handler(mlx_key_data_t key, void *param);

void move_player(void *param);

// render
void clear_image(t_cub *cub);
float distance(float x, float y);
float fixed_dist(t_cub *cub, float x1, float y1, float x2, float y2);
bool touch(t_cub *cub, float px, float py);

// main

void cast_ray(t_cub *cub, float angle, float *hit_x, float *hit_y, float *perp_dist);
void put_pixel(t_cub *cub, int x, int y, uint32_t color_rgb);



void	parse_all_wall_textures(t_cub *cub, char *line, int i, int *success);
int	check_png_extension(char *path);
char	*extract_texture_path(char *line, int offset);

void	parse_colors(t_cub *cub, char *line, int i, int *succes);


void	free_map_array(t_cub *cub);


// render

void	draw_textured_slice(t_cub *cub, int screen_x, t_wall_hit *hit, int line_height);



#endif