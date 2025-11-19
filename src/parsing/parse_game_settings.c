/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_game_settings.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:39:51 by ajelloul          #+#    #+#             */
/*   Updated: 2025/11/19 09:40:16 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	validate_textures_and_colors(t_cub *cub)
{
	if (cub->list_status.is_wrong_txtr_extension)
		return (display_errors("Wrong texture extension: must be [.png]\n"), 1);
	if (cub->list_status.is_duplicate_key)
		return (display_errors("Error: Duplicate components\n"), 1);
	if (cub->list_status.invalid_key)
		return (display_errors("Error: Invalid key\n"), 1);
	return (0);
}

/*
 read textures path + colors only until succes = 6
*/

/*
	TODO:
		parse wall and save path
		parse color and save the floor and ceil
*/

static int	read_until_complete(t_cub *cub, int fd, int *count)
{
	char	*line;
	int		offset;

	line = get_next_line(fd);
	while (line)
	{
		trim_newline(line);
		offset = skip_spaces(&line);
		if (!configuration_key(cub, line, offset, count))
		{
			if (line)
				free(line);
			break ;
		}
		if (line)
			free(line);
		if (*count == 6)
			break ;
		line = get_next_line(fd);
	}
	return (0);
}

int	parse_game_settings(t_cub *cub, int fd)
{
	int	success_count;

	success_count = 0;
	read_until_complete(cub, fd, &success_count);
	delete_duplicate_list(cub->duplicate_list);
	cub->duplicate_list = NULL;
	return (validate_textures_and_colors(cub));
}

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
