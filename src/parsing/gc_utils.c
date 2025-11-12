/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 12:17:31 by ajelloul          #+#    #+#             */
/*   Updated: 2025/11/12 13:46:26 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_map_array(t_cub *cub)
{
	int	row;

	if (!cub->map.map)
		return ;
	row = 0;
	while (row < cub->map.height)
	{
		if (cub->map.map[row])
		{
			free(cub->map.map[row]);
			cub->map.map[row] = NULL;
		}
		row++;
	}
	free(cub->map.map);
	cub->map.map = NULL;
}

static void	free_single_path(char **path)
{
	if (*path)
	{
		free(*path);
		*path = NULL;
	}
}

void	delete_textures_paths(t_cub *cub)
{
	free_single_path(&cub->no_texture_path);
	free_single_path(&cub->ea_texture_path);
	free_single_path(&cub->so_texture_path);
	free_single_path(&cub->we_texture_path);
}

static void	destroy_one_textr(mlx_texture_t **texture)
{
	if (!*texture)
		return ;
	mlx_delete_texture(*texture);
	*texture = NULL;
}

void	delete_mlx_images(t_cub *cub)
{
	destroy_one_textr(&cub->textures.mlx_east);
	destroy_one_textr(&cub->textures.mlx_north);
	destroy_one_textr(&cub->textures.mlx_south);
	destroy_one_textr(&cub->textures.mlx_west);
}
