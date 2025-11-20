/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-krai <ael-krai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 19:05:52 by ael-krai          #+#    #+#             */
/*   Updated: 2025/11/20 10:51:18 by ael-krai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void    key_press(t_cub *cub, int key)
{
    if (key == MLX_KEY_W)
        cub->player.key_up = true;
    else if (key == MLX_KEY_S)
        cub->player.key_down = true;
    else if (key == MLX_KEY_A)
        cub->player.key_left = true;
    else if (key == MLX_KEY_D)
        cub->player.key_right = true;
    else if (key == MLX_KEY_LEFT)
        cub->player.left_rotate = true;
    else if (key == MLX_KEY_RIGHT)
        cub->player.right_rotate = true;
    else if (key == MLX_KEY_ESCAPE)
    {
        shutdown_cub(cub);
        exit(0);
    }
}

void    key_release(t_cub *cub, int key)
{
    if (key == MLX_KEY_W)
		cub->player.key_up = false;
    else if (key == MLX_KEY_S)
		cub->player.key_down = false;
    else if (key == MLX_KEY_A)
		cub->player.key_left = false;
    else if (key == MLX_KEY_D)
		cub->player.key_right = false;
    else if (key == MLX_KEY_LEFT)
		cub->player.left_rotate = false;
    else if (key == MLX_KEY_RIGHT)
		cub->player.right_rotate = false;
}

void    key_handler(mlx_key_data_t key, void *param)
{
    t_cub *cub = (t_cub *)param;

    if (key.action == MLX_PRESS)
        key_press(cub, key.key);
    else if (key.action == MLX_RELEASE)
        key_release(cub, key.key);
}
