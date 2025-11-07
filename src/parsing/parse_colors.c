/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 15:49:38 by ajelloul          #+#    #+#             */
/*   Updated: 2025/11/03 10:43:36 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/cub3d.h"


void	add_key_to_duplicate_list(t_duplicat_list **list, char *key)
{
	t_duplicat_list	*new_node;
	t_duplicat_list	*tail;

	new_node = malloc(sizeof(t_duplicat_list));
	if (!new_node)
		return ;
	new_node->key = key;
	new_node->next = NULL;
	if (!*list)
	{
		*list = new_node;
		return ;
	}
	tail = *list;
	while (tail->next)
		tail = tail->next;
	tail->next = new_node;
}

int	is_duplicate(t_duplicat_list **list, char *key)
{
	t_duplicat_list	*current;
	int				key_length;

	key_length = ft_strlen(key);
	current = *list;
	while (current)
	{
		if (ft_strncmp(current->key, key, key_length + 1) == 0)
			return (1);
		current = current->next;
	}
	add_key_to_duplicate_list(list, key);
	return (0);
}

void	free_rbg_values(char **value)
{
	int	idx;

	idx = 0;
	while (value[idx])
	{
		free(value[idx]);
		value[idx] = NULL;
		idx++;
	}
	free(value);
	value = NULL;
}
static bool	is_valid_format(char *str)
{
	int	commas;
	int	i;

	commas = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			commas++;
		i++;
	}
	return (commas == 2);
}


/*

	It builds one single integer that represents a color  with red, green, blue (transparency) combined together
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
