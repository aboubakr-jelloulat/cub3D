/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 15:45:17 by ajelloul          #+#    #+#             */
/*   Updated: 2025/11/03 09:27:13 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
	check is duplicate avoid :
		WE textures/wall_we.png
		WE textures/wall_we.png
	
	
	extract texture path :
		
	
*/

static void	parse_north_texture(t_cub *cub, char *line, int *count)
{
	char	*path;
	int		len;

	if (is_duplicate(&cub->duplicate_list, "NO"))
	{
		cub->list_status.is_duplicate_key = true;
		return ;
	}
	path = extract_texture_path(line, 3);
	if (!path)
		return ;
	len = ft_strlen(path);
	if (ft_strncmp(path + len - 4, ".png", 4) != 0)
	{
		cub->list_status.is_wrong_txtr_extension = true;
		free(path);
		return ;
	}
	cub->no_texture_path = path;
	(*count)++;
}

static void	parse_south_texture(t_cub *cub, char *line, int *count)
{
	char	*path;
	int		len;

	if (is_duplicate(&cub->duplicate_list, "SO"))
	{
		cub->list_status.is_duplicate_key = true;
		return ;
	}
	path = extract_texture_path(line, 3);
	if (!path)
		return ;
	len = ft_strlen(path);
	if (ft_strncmp(path + len - 4, ".png", 4) != 0)
	{
		cub->list_status.is_wrong_txtr_extension = true;
		free(path);
		return ;
	}
	cub->so_texture_path = path;
	(*count)++;
}

static void	parse_west_texture(t_cub *cub, char *line, int *count)
{
	char	*path;
	int 	len;

	if (is_duplicate(&cub->duplicate_list, "WE"))
	{
		cub->list_status.is_duplicate_key = true;
		return ;
	}
	path = extract_texture_path(line, 3);
	if (!path)
		return ;
	len = ft_strlen(path);
	if (ft_strncmp(path + len - 4, ".png", 4) != 0)
	{
		cub->list_status.is_wrong_txtr_extension = true;
		free(path);
		return ;
	}
	cub->we_texture_path = path;
	(*count)++;
}

static void	parse_east_texture(t_cub *cub, char *line, int *count)
{
	char	*path;
	int 	len;

	if (is_duplicate(&cub->duplicate_list, "EA"))
	{
		cub->list_status.is_duplicate_key = true;
		return ;
	}
	path = extract_texture_path(line, 3);
	if (!path)
		return ;
	len = ft_strlen(path);
	if (ft_strncmp(path + len - 4, ".png", 4) != 0)
	{
		cub->list_status.is_wrong_txtr_extension = true;
		free(path);
		return ;
	}
	cub->ea_texture_path = path;
	(*count)++;
}

/*
	i = offset

	Parse all wall textures and check if is dupliacte
*/
void	parse_all_wall_textures(t_cub *cub, char *line, int i, int *success)
{
	if (ft_strncmp(line + i, "NO ", 3) == 0)
		parse_north_texture(cub, line + i, success);
	else if (ft_strncmp(line + i, "SO ", 3) == 0)
		parse_south_texture(cub, line + i, success);
	else if (ft_strncmp(line + i, "WE ", 3) == 0)
		parse_west_texture(cub, line + i, success);
	else if (ft_strncmp(line + i, "EA ", 3) == 0)
		parse_east_texture(cub, line + i, success);
}
