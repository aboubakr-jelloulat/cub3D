/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 09:51:40 by ajelloul          #+#    #+#             */
/*   Updated: 2025/11/12 13:31:13 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_game(t_cub *cub)
{
	cub->player.x *= BLOCK;
	cub->player.y *= BLOCK;
	cub->player.angle = cub->player.radius;
	cub->player.key_up = false;
	cub->player.key_down = false;
	cub->player.key_right = false;
	cub->player.key_left = false;
	cub->player.left_rotate = false;
	cub->player.right_rotate = false;
	cub->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", false);
	cub->image = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(cub->mlx, cub->image, 0, 0);
}

int	init_textures(t_cub *cub)
{
	cub->textures.mlx_north = mlx_load_png(cub->no_texture_path);
	cub->textures.mlx_south = mlx_load_png(cub->so_texture_path);
	cub->textures.mlx_west = mlx_load_png(cub->we_texture_path);
	cub->textures.mlx_east = mlx_load_png(cub->ea_texture_path);
	if (!cub->textures.mlx_north
		|| !cub->textures.mlx_south
		|| !cub->textures.mlx_west
		|| !cub->textures.mlx_east)
	{
		display_errors("\nfailed to load textures\n");
		return (1);
	}
	return (0);
}

void	debug(t_cub *cub)
{
	int	i;

	printf("Map height: %d\n", cub->map.height);
	printf("Map width: %d\n", cub->map.width);
	i = -1;
	while (++i < cub->map.height)
		printf("[%s]\n", cub->map.map[i]);
	printf("NO: %s\n", cub->no_texture_path);
	printf("SO: %s\n", cub->so_texture_path);
	printf("WE: %s\n", cub->we_texture_path);
	printf("EA: %s\n", cub->ea_texture_path);
	printf("F: %d, in rgb r: %d, g: %d, b: %d\n", cub->list_status.floor_color,
		(cub->list_status.floor_color >> 16) & 0xFF,
		(cub->list_status.floor_color >> 8) & 0xFF,
		cub->list_status.floor_color & 0xFF);
	printf("C: %d, in rgb r: %d, g: %d, b: %d\n", cub->list_status.ceiling_color,
		(cub->list_status.ceiling_color >> 16) & 0xFF,
		(cub->list_status.ceiling_color >> 8) & 0xFF,
		cub->list_status.ceiling_color & 0xFF);
	printf("Player position: x=%d, y=%d, angle=%.2f\n",
		cub->player.x, cub->player.y, cub->player.radius);
}

int	load_map_data(t_cub *cub, int ac, char **av)
{
	int	fd;

	if (ac != 2)
	{
		display_errors("Invalid arguments Usage: ./cub3D maps/[map.cub]\n");
		return (1);
	}
	if (open_and_validate_file(av[1], &fd))
		return (1);
	if (parse_game_settings(cub, fd))
		return (1);
	if (parse_map(cub, fd))
		return (1);
	debug(cub);
	close(fd);
	if (validate_and_set_player(cub))
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_cub	cub;

	ft_bzero(&cub, sizeof(t_cub));
	if (load_map_data(&cub, ac, av) == 1)
		return (shutdown_cub(&cub), 1);
	if (init_textures(&cub) == 1)
		return (shutdown_cub(&cub), 1);
	init_game(&cub);
	mlx_key_hook(cub.mlx, key_handler, &cub);
	mlx_loop_hook(cub.mlx, draw_loop, &cub);
	mlx_loop(cub.mlx);
	shutdown_cub(&cub);
	return (0);
}
