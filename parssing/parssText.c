/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssText.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haalouan <haalouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:43:56 by haalouan          #+#    #+#             */
/*   Updated: 2024/10/16 18:06:20 by haalouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	put_c(char **str, t_map *textures)
{
	int	i;
	int	save;
	int	flag;

	i = 0;
	flag = 0;
	while (str && str[i] && str[i][0] != '1')
	{
		str[i] = escape_spaces(str[i]);
		if (ft_strncmp(str[i], "C", 1) == 0 && (str[i][1] == ' ' || str[i][1] == '\t'))
		{
			flag++;
			save = i;
		}
		i++;
	}
	if (flag != 1)
		manage_error(str, textures);
	if (flag == 1)
	{
		str[save] = escape_spaces(str[save]);
		textures->c = put_map(str[save], 1);
	}
}

void	put_0_1(char **str, t_map *textures)
{
	int		i;
	char	*save;
	char	*re;
	int		k;

	i = 0;
	k = 0;
	i = check_map_valid(str);
	textures->map = allocate_map(count_map(str + i));
	while (str && str[i])
	{
		save = ft_strdup(str[i]);
		re = ft_strtrim(save, "\n");
		free(save);
		textures->map[k] = ft_strdup(re);
		free(re);
		k++;
		i++;
	}
}

void	parsse_textures(char **str, t_map *textures)
{
	put_no(str, textures);
	put_so(str, textures);
	put_we(str, textures);
	put_ea(str, textures);
	put_f(str, textures);
	put_c(str, textures);
	check_f_c(str, textures);
	put_0_1(str, textures);
}

char	*escape_spaces(char *str)
{
	char	*s;
	char	*re;

	s = ft_strtrim(str, " ");
	free(str);
	re = ft_strtrim(s, "\t");
	free(s);
	return (re);
}

char	*put_map(char *str, int plus)
{
	char	*s;
	char	*re;
	int		i;

	s = NULL;
	i = plus;
	while (str && str[i] && str[i] == ' ' && str[i] == '\t')
		i++;
	s = ft_strdup(str + i);
	re = ft_strtrim(s, "\n");
	free(s);
	re = escape_spaces(re);
	return (re);
}
