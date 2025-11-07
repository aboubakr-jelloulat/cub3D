/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 12:20:30 by ael-krai          #+#    #+#             */
/*   Updated: 2025/11/06 10:46:51 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	update_direction(t_cub *cub, t_player *player, float dx, float dy)
{
	float	new_x;
	float	new_y;

	new_x = player->x + dx;
	new_y = player->y + dy;
	if (!touch(cub, new_x, new_y))
	{
		player->x = new_x;
		player->y = new_y;
	}
}

void	rotate_player(t_player *player)
{
    if (player->left_rotate)
        player->angle -= ANGLE_SPEED;
    if (player->right_rotate)
        player->angle += ANGLE_SPEED;
    if (player->angle > 2 * PI)
        player->angle = 0;
    if (player->angle < 0)
        player->angle = 2 * PI;
}

void	redirect_player(t_cub *cub, t_player *player)
{
	float	cos_angle;
	float	sin_angle;
	int		speed;

	speed = 6;
	cos_angle = cosf(player->angle);
	sin_angle = sinf(player->angle);
	if (player->key_up == true)
		update_direction(cub, player, cos_angle * speed, sin_angle * speed);
	else if (player->key_down == true)
		update_direction(cub, player, -cos_angle * speed, -sin_angle * speed);
	else if (player->key_left == true)
		update_direction(cub, player, sin_angle * speed, -cos_angle * speed);
	else if (player->key_right == true)
		update_direction(cub, player, -sin_angle * speed, cos_angle * speed);
}

void	move_player(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	rotate_player(&cub->player);
	redirect_player(cub, &cub->player);
}
