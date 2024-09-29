/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:52:27 by obrittne          #+#    #+#             */
/*   Updated: 2024/09/29 15:36:14 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	transform_to_channel(double v)
{
	if (v < 0.0)
		v = 0.0;
	if (v > 1.0)
		v = 1.0;
	return ((int)(v * 255.0));
}

uint32_t	get_color_from_vec3(t_vec3 vec)
{
	uint32_t	res;

	res = transform_to_channel(vec.x) << 24 | transform_to_channel(vec.y) << 16 | transform_to_channel(vec.z) << 8 | 255;
	return (res);
}

void	closest_hit(t_data *data, t_ray *ray, t_hit *hit)
{
	t_vec3	origin;

	(void)data;
	if (hit->type == 1)
	{
		origin = \
		subtract(ray->ray_origin, hit->cords);
		hit->world_position = add(origin, scale(ray->ray_direction, hit->hit_distance));
		hit->world_normal = normalize(hit->world_position);
		hit->world_position = \
		add(hit->world_position, hit->cords);
	}
	else if (hit->type == 2)
	{
		hit->world_position = add(ray->ray_origin, scale(ray->ray_direction, hit->hit_distance));
		hit->world_normal = hit->normal;
	}
	else if (hit->type == 3)
	{
		hit->world_position = add(ray->ray_origin, scale(ray->ray_direction, hit->hit_distance));
		hit->world_normal = normalize(subtract(hit->world_position, add(hit->cords, scale(hit->normal, dot_product(subtract(hit->world_position, hit->cords), hit->normal)))));
	}
	else if (hit->type == 4)
	{
		hit->world_position = add(ray->ray_origin, scale(ray->ray_direction, hit->hit_distance));
		hit->world_normal = normalize(subtract(subtract(hit->world_position, hit->cords), scale(hit->normal, dot_product(subtract(hit->world_position, hit->cords), hit->normal))));
	}
}

void	ray_trace(t_data *data, t_ray *ray, t_hit *hit)
{

	hit->found = 0;
	hit->hit_distance = MAXFLOAT;
	handle_spheres(data, ray, hit);
	handle_planes(data, ray, hit);
	handle_cylinders(data, ray, hit);
	// handle_cones(data, ray, hit);
	closest_hit(data, ray, hit);
}

uint32_t	per_pixel(t_data *data, t_ray *ray, uint32_t x, uint32_t y)
{

	t_hit 	hit;
	// double	dist;
	// t_vec3	light_dir;
	t_vec3	color;

	ray->ray_direction = get_direction_ray(data, ((double)x / \
	(double)data->image->width) * 2.0 - 1.0, (1.0 - (double)y / \
	(double)data->image->height) * 2.0 - 1.0);
	ray_trace(data, ray, &hit);
	if (hit.found == 0)
		return (255);
	// light_dir = subtract(data->light.vec3_cords, hit.world_position);
	// dist = sqrt(dot_product(light_dir, light_dir));
	// light_dir = normalize(light_dir);

	// double d = max_double(dot_product(hit.world_normal, light_dir), 0.0);
	// if (d != 0.0)
	// {
	// 	t_hit new;
	// 	ray->ray_origin = add(hit.world_position, scale(light_dir, 0.00001));
	// 	ray->ray_direction = light_dir;
	// 	ray_trace(data, ray, &new);
	// 	if (new.found != 0 && new.hit_distance < dist)
	// 	{
	// 		d = 0;
	// 	}
	// }
	// d *= data->light.ratio;

	// // dprintf(1, "%f  ", d);
	// t_vec3 obj_color = hit.color;
	// t_vec3 color = multiply_vec3(obj_color, create_vec3_color_arr(data->light.colors));
	// color = scale(color, d);


	
	// t_vec3 ambient_color = create_vec3_color_arr(data->ambitient_light.colors);
    // t_vec3 ambient_component = multiply_vec3(obj_color, ambient_color);
    // ambient_component = scale(ambient_component, data->ambitient_light.ratio * data->light.ratio);

	// t_vec3 final_color = add(color, ambient_component);
	// // t_vec3 final_color = color;
	// final_color = shrink_vec3(final_color, 0.0, 1.0);
	color = calculate_light(data, ray, &hit);
	return (get_color_from_vec3(shrink_vec3(color, 0.0, 1.0)));
}


int	displaying(t_data *data)
{
	uint32_t	y;
	uint32_t	x;
	uint32_t	pixel;
	t_ray		ray;

	y = 0;
	while (y < data->image->height)
	{
		x = 0;
		while (x < data->image->width)
		{
			ray.ray_origin = create_vec3_arr(data->camera.cords);
			pixel = per_pixel(data, &ray, x, y);
			mlx_put_pixel(data->image, x, y, pixel);
			x++;
		}
		y++;
	}
	return (1);
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
