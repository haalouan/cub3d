/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:57:12 by shamdoun          #+#    #+#             */
/*   Updated: 2024/10/20 17:41:32 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	init_wall_values(t_map_e *m, t_wall *w)
{
	// w->distance_to_projection = (m->width * BLOCK_W / 2)
	// 	/ tan(FOV / 2 * (M_PI / 180));
	(void)m;
	w->distance_to_projection = (W_WIDTH * BLOCK_W / 2)
		/ tan(FOV / 2 * (M_PI / 180));
}

double	nor_angle(double angle)	// normalize the angle
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}


void	update_wall_values(t_wall *w, t_ray *rays, t_map_e *m)
{
	update_texture(w, rays, m);
	w->distance = rays->distance;
	if (w->distance < 0)
		printf("fabs does not work\n");
	w->distance = ft_fabs(cos((m->player->angle - rays->angle)
			* (M_PI / 180)) * w->distance);
	// w->distance = cos((m->player->angle - rays->angle)
	// 		* (M_PI / 180)) * w->distance;
	w->wall_height = ((w->distance_to_projection * BLOCK_L) / w->distance);
	// w->wall_top = ((BLOCK_L * m->height) / 2)
	// 	- ((w->wall_height / 2));
	w->wall_top = (((BLOCK_L * W_HEIGHT) / 2)
		- ((w->wall_height / 2)));
	// if (w->wall_top < 0 || (w->wall_top > W_HEIGHT * BLOCK_L))
	// 	w->wall_top = 0;
	if (w->wall_top < 0)
		w->wall_top = 0;
	// if (w->wall_top < 0 || (w->wall_top > m->height * BLOCK_L))
	// 	w->wall_top = 0;
	w->wall_bot = absolute_value((BLOCK_L * W_HEIGHT) / 2) + ((w->wall_height / 2));
	// w->wall_bot = ((BLOCK_L * m->height) / 2) + ((w->wall_height / 2));
	if (absolute_value(w->wall_bot) > W_HEIGHT * BLOCK_L)
		w->wall_bot = W_HEIGHT * BLOCK_L;
	// if (absolute_value(w->wall_bot) > m->height * BLOCK_L)
	// 	w->wall_bot = m->height * BLOCK_L;
	if (w->wall_bot == w->wall_top)
		printf("angle is  %f\n", rays->angle);
	w->t->offset_x = (int)((rays->bitmap_offset)
			* (w->t->texture->width / BLOCK_W)) % (w->t->texture->width);
	if (w->t->offset_x < 0)
		w->t->offset_x = 0;
	w->t->scaling_factor = ((double)w->t->texture->height / w->wall_height);
	w->angle = rays->angle;
}

void	draw_wall(t_wall *w, t_map_e *m, int x, int vertical)
{
	int	y;
	int	b;

	(void)vertical;
	y = w->wall_top;
	b = w->wall_bot;
	w->t->offset_y = (int)(((w->wall_top - (W_HEIGHT * BLOCK_L / 2)
				+ (w->wall_height / 2)) * w->t->scaling_factor)) % (w->t->texture->height);
	// w->t->offset_y = ((w->wall_top - (m->height * BLOCK_L / 2)
	// 			+ (w->wall_height / 2)) * w->t->scaling_factor);
	if (w->t->offset_y < 0)
		w->t->offset_y = 0;
	while (y < b)
	{
		w->t->color = w->t->arr[((int)w->t->offset_y
				* w->t->texture->width) + (int)w->t->offset_x];
		w->t->color = convert_pixel_to_color(w->t->color);
		mlx_put_pixel(m->interface->new_img,
			x, y, w->t->color);
		w->t->offset_y += w->t->scaling_factor;
		y++;
	}
}

void	render_wall(t_map_e *m, t_ray *ray, t_wall *w, int x)
{
	update_wall_values(w, ray, m);
	draw_sky(m, x, w);
	draw_wall(w, m, x, ray->hit_vertical);
	draw_floor(w, m, x);
}

void	draw_3d_walls(t_map_e *m)
{
	static t_wall	*w;

	if (!w)
	{
		w = ft_malloc(sizeof(t_wall), 0);
		if (!w)
			exit(1);
		w->t = ft_malloc(sizeof(t_bitmap), 0);
	}
	init_wall_values(m, w);
	draw_all_walls(m, w);
}
