/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajelloul <ajelloul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 10:34:44 by ajelloul          #+#    #+#             */
/*   Updated: 2025/11/01 11:17:20 by ajelloul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"



int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t');
}

bool	is_space(char c)
{
	return (c == 32);
}

void	trim_newline(char *str)
{
	int	pos;

	pos = 0;
	while (str[pos])
	{
		if (str[pos] == '\n')
		{
			str[pos] = '\0';
			return ;
		}
		pos++;
	}
}

int	skip_spaces(char **line)
{
	int	offset;

	offset = 0;
	while ((*line)[offset] == ' ' || (*line)[offset] == '\t')
		offset++;
	return (offset);
}
