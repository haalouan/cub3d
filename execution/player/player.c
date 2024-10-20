/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:29:42 by shamdoun          #+#    #+#             */
/*   Updated: 2024/10/20 13:01:39 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	init_player_instance(t_map_e *map3d, t_map *data)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	map3d->player = ft_malloc(sizeof(t_player), 0);
	if (!map3d->player)
		free_all_exit(map3d, data);
	while (i < map3d->height)
	{
		if (!row_empty(data->map[i]))
		{
			j = 0;
			k = ft_strlen(data->map[i]);
			while (j < k && j < map3d->width)
			{
				if (ft_isalpha(data->map[i][j]))
				{
					init_player_position(map3d->player, i, j, data->map[i][j]);
					return ;
				}
				j++;
			}
		}
		i++;
	}
}

static double	extract_angle(char d)
{
	if (d == 'E')
		return (0);
	if (d == 'N')
		return (90);
	if (d == 'W')
		return (180);
	return (270);
}

void	init_player_position(t_player *p, int i, int j, char direction)
{
	p->x_p = j * BLOCK_W + 40;
	p->y_p = i * BLOCK_L + 40;
	p->angle = extract_angle(direction);
}

static void	draw_circle(t_map_e *map, int x_center, int y_center, int radius)
{
	int	dx;
	int	dy;
	int	i;
	int	j;
	
	i = 0;
	while (i <= radius * 2)
	{
		dx = i - radius;
		j = 0;
		while (j <= radius * 2)
		{
			dy = j - radius;
			if (dx * dx + dy * dy <= radius * radius)
				my_put_mlx(map, x_center + dx, y_center + dy);
				// mlx_put_pixel(m->interface->new_img, x_center + dx, y_center + dy)
			j++;
		}
		i++;
	}
}

void	draw_player(t_map_e *map, t_minimap *mini)
{
	int	x_center;
	int	y_center;
	int	radius;

(void)mini;
	x_center = cast_to_minimap(map->player->x_p, mini->begin_y, mini->end_y , 0) ;
	y_center = cast_to_minimap((map->player->y_p), mini->begin_x, mini->end_x, 1) ;
	radius = 10;
	draw_circle(map, x_center, y_center, radius);
	map->minimap = mini;
	apply_dda_algorithm(map);
}
