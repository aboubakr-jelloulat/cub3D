/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 10:49:02 by ajelloul          #+#    #+#             */
/*   Updated: 2025/11/05 15:48:11 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"



void	delete_duplicate_list(t_duplicat_list *list)
{
	t_duplicat_list	*next;

	while (list)
	{
		next = list->next;
		free(list);
		list = next;
	}
}

void	delete_map_rows(t_map_row *map_row)
{
	t_map_row	*next;

	while (map_row)
	{
		next = map_row->down_row;
		free(map_row->row);
		free(map_row);
		map_row = next;
	}
}

void	gc_collect(t_cub *cub)
{
	delete_textures_paths(cub);
	delete_mlx_images(cub);
	free_map_array(cub);
}

int	shutdown_cub(t_cub *cub)
{
	if (cub->mlx)
		mlx_close_window(cub->mlx);
	if (cub->image)
		mlx_delete_image(cub->mlx, cub->image);
	gc_collect(cub);
	ft_bzero(cub, sizeof(t_cub));
	return (0);
}
