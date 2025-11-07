/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 11:56:13 by ajelloul          #+#    #+#             */
/*   Updated: 2025/11/04 13:19:00 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
	width → the longest row length (number of columns)

	height → the total number of rows

*/
static void	calculate_dimensions(t_map_row *rows, int *width, int *height)
{
	t_map_row	*current;

	*width = 0;
	*height = 0;
	current = rows;
	while (current)
	{
		if (current->size > *width)
			*width = current->size;
		(*height)++;
		current = current->down_row;
	}
}

// Fill the 2D map array from linked list of rows
static int	fill_map_array(t_cub *cub, t_map_row *rows, int width)
{
	t_map_row	*current;
	int			i;

	current = rows;
	i = 0;
	while (current)
	{
		cub->map.map[i] = malloc(sizeof(char) * (width + 1));
		if (!cub->map.map[i])
			return (1);
		
		ft_memset(cub->map.map[i], ' ', width);
		cub->map.map[i][width] = '\0';
	
		ft_memcpy(cub->map.map[i], current->row, current->size);
		current = current->down_row;
		i++;
	}
	return (EXIT_SUCCESS);
}

// Main function: convert linked list of rows to 2D array
int	init_map_from_rows(t_cub *cub, t_map_row *rows)
{
	int	width;
	int	height;

	calculate_dimensions(rows, &width, &height);
	cub->map.width = width;
	cub->map.height = height;
	
	cub->map.map = malloc(sizeof(char *) * height);
	if (!cub->map.map)
		return (1);
	return (fill_map_array(cub, rows, width));
}

