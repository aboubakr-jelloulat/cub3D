/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 09:58:07 by ajelloul          #+#    #+#             */
/*   Updated: 2025/11/19 09:37:50 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	extract_basename(char *filename, char **base)
{
	char	*separator;

	separator = ft_strrchr(filename, '/');
	if (separator)
		*base = separator + 1;
	else
		*base = filename;
	return (0);
}

static int	check_extension_format(char *filename, int len)
{
	if (len < 5)
		return (1);
	if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		return (1);
	return (0);
}

/*
	./cub3D maps/.cub
*/
int	valid_file_extension(char *filename)
{
	int		len;
	char	*base;

	if (!filename)
	{
		display_errors("Invalid filename\n");
		return (1);
	}
	len = ft_strlen(filename);
	if (check_extension_format(filename, len))
	{
		display_errors("file must be a [.cub]\n");
		return (1);
	}
	extract_basename(filename, &base);
	if (ft_strncmp(base, ".cub", 5) == 0)
	{
		display_errors("filename cannot be just '.cub'\n");
		return (1);
	}
	return (0);
}

static int	open_map_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		display_errors("Can't open This file\n");
		return (-1);
	}
	return (fd);
}

int	open_and_validate_file(char *filepath, int *fd_out)
{
	if (valid_file_extension(filepath))
		return (1);
	*fd_out = open_map_file(filepath);
	if (*fd_out == -1)
		return (1);
	return (0);
}
