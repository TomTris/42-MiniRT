/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdo <qdo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:34:46 by qdo               #+#    #+#             */
/*   Updated: 2024/10/03 15:53:06 by qdo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt_bonus.h"

void	mem_set_0(void *a, size_t len)
{
	size_t	i;
	char	*b;

	b = (char *)a;
	i = 0;
	while (i < len)
	{
		b[i] = 0;
		i++;
	}
}

void	set_type_distance_cy2(t_hit *hit, double dist, int var)
{
	hit->type = 3;
	hit->hit_distance = dist;
	hit->type_cy = var;
}

typedef struct s_vars_d
{
	int			y;
	int			x;
	t_vec3		pixel;
	t_ray		ray;
	int			*index;
	int			ind;
}	t_vars_d;

t_vec3	per_pixel(t_data *data, t_ray *ray, uint32_t x, uint32_t y)
{
	t_hit	hit;
	t_vec3	color;

	hit.checkers = 0;
	ray->ray_direction = get_direction_ray(data, ((double)x / \
	(double)data->image->width) * 2.0 - 1.0, (1.0 - (double)y / \
	(double)data->image->height) * 2.0 - 1.0);
	mem_set_0(&hit, sizeof(t_hit));
	ray_trace(data, ray, &hit);
	if (hit.found == 0)
		return (create_vec3(0, 0, 0));
	color = calculate_light(data, ray, &hit);
	return (color);
}

void	*displaying(void *input)
{
	t_data		*data;
	t_vars_d	vars;

	data = ((t_input *)input)->data;
	vars.ind = (((t_input *)input)->ind);
	vars.y = -1;
	while (++vars.y < (int)data->image->height)
	{
		vars.x = -1;
		while (++vars.x < (int)data->image->width)
		{
			if (vars.x % AMOUNT_OF_THREADS == vars.ind)
			{
				vars.ray.ray_origin = data->camera.vec3_cords;
				vars.pixel = per_pixel(data, &vars.ray, vars.x, vars.y);
				mlx_put_pixel(data->image, vars.x, vars.y, \
				get_color_from_vec3(vars.pixel));
			}
		}
	}
	return (NULL);
}

void	display(t_data *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "Scene", true);
	if (!data->mlx)
		return (display_error_message("Couldnt init window"));
	data->image = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->image)
		return (display_error_message("Couldnt create image"), \
		mlx_close_window(data->mlx));
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) == -1)
		return (mlx_delete_image(data->mlx, data->image), \
		mlx_close_window(data->mlx), \
		display_error_message("Couldnt put image to window"));
	mlx_loop_hook(data->mlx, ft_hook_keys, data);
	mlx_loop_hook(data->mlx, change_image_size_hook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
}
