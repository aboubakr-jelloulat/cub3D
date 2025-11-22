/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 09:43:54 by ajelloul          #+#    #+#             */
/*   Updated: 2025/11/22 15:38:23 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "/Users/ael-krai/MLX42/include/MLX42/MLX42.h"

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <math.h>
# include "../shared/libft/libft.h"
# include "../shared/gnl/get_next_line.h"
# include "prototypes.h"
# include "structs.h"

# define RED "\033[31m"
# define RESET "\033[0m"

# define PI 3.14159265359f
# define FOV 1.0471975512f /* equivalent to PI / 3 */
# define WIDTH 1280
# define HEIGHT 800
# define BLOCK 64
# define PLAYER_SPEED 6.0f
# define ANGLE_SPEED 0.03f

# define COLOR_WALL 0xFFFFFF
# define COLOR_RAY 0xFF0000
# define COLOR_PLAYER 0x00FF00
# define COLOR_BG 0x000000

#endif
