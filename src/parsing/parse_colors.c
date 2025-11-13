/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 15:49:38 by ajelloul          #+#    #+#             */
/*   Updated: 2025/11/13 09:20:03 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
	It builds one single integer that represents a color  with 
		red, green, blue (transparency) combined together
	he vertical bar | is bitwise OR  it combines all bits together
*/
static int	build_color(int r, int g, int b)
{
	return ((r << 24) | (g << 16) | (b << 8) | 255);
}

int	parse_color_value(char *line, int *out_color)
{
	char	**parts;
	int		r;
	int		g;
	int		b;

	if (!is_valid_format(line))
		return (0);
	parts = ft_split(line, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2])
	{
		free_rbg_values(parts);
		return (0);
	}
	r = ft_atoi(parts[0]);
	g = ft_atoi(parts[1]);
	b = ft_atoi(parts[2]);
	free_rbg_values(parts);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (0);
	*out_color = build_color(r, g, b);
	return (1);
}

static void	handle_floor_color(t_cub *cub, char *line, int *count)
{
	if (is_duplicate(&cub->duplicate_list, "F"))
		cub->list_status.is_duplicate_key = true;
	if (parse_color_value(line + 1, &cub->list_status.floor_color))
		(*count)++;
}

static void	handle_ceiling_color(t_cub *cub, char *line, int *count)
{
	if (is_duplicate(&cub->duplicate_list, "C"))
		cub->list_status.is_duplicate_key = true;
	if (parse_color_value(line + 1, &cub->list_status.ceiling_color))
		(*count)++;
}

void	parse_colors(t_cub *cub, char *line, int i, int *succes)
{
	char	color;

	color = line[i];
	if (color == 'F')
		handle_floor_color(cub, line + i, succes);
	else if (color == 'C')
		handle_ceiling_color(cub, line + i, succes);
}
