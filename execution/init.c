/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:08:52 by shamdoun          #+#    #+#             */
/*   Updated: 2024/10/16 19:53:28 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	calculate_dimensions(t_map_e *m, t_map *data)
{
	int	i;
	int	height;
	int	width;
	int	tmp;

	i = 0;
	height = 0;
	width = 0;
	while (data->map[i++])
		height++;
	i = 0;
	while (data->map[i])
	{
		tmp = ft_strlen(data->map[i]);
		if (tmp > width)
			width = tmp;
		i++;
	}
	m->width = width;
	m->height = height;
}

static void	init_interface(t_map_e *m, t_map *data)
{
	m->interface = ft_malloc(sizeof(t_map), 0);
	if (!m->interface)
		free_all_exit(m, data);
	m->interface->mlx_ptr = mlx_init(W_WIDTH * BLOCK_W,
			W_HEIGHT * BLOCK_L, "overall_map", false);
	if (!m->interface->mlx_ptr)
		free_all_exit(m, data);
	m->interface->new_img = mlx_new_image(m->interface->mlx_ptr,
			W_WIDTH * BLOCK_W, W_HEIGHT * BLOCK_L);
	if (!m->interface->new_img)
		free_all_exit(m, data);
}

uint32_t	extract_color(char *c, t_map_e *m, t_map *data)
{
	char		**split;
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;

	split = ft_split(c, ',');
	if (!split)
		free_all_exit(m, data);
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	return ((uint32_t)get_rgba(r, g, b, 100));
}

static void	init_colors(t_map_e *m, char *f, char *c, t_map *data)
{
	m->floor = extract_color(f, m, data);
	m->ceiling = extract_color(c, m, data);
}

void	init_all_values(t_map_e *m, t_map *data)
{
	init_textures(m, data);
	calculate_dimensions(m, data);
	init_player_instance(m, data);
	init_colors(m, data->f, data->c, data);
	m->m_values = data->map;
	init_interface(m, data);
}
