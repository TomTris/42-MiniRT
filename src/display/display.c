/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:52:27 by obrittne          #+#    #+#             */
/*   Updated: 2024/09/22 14:14:36 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	make_image_black(mlx_image_t *image)
{
	uint8_t		*pixels;
	uint32_t	i;

	pixels = image->pixels;
	i = 0;
	while (i < image->width * image->height)
	{
		pixels[i * 4] = 0;
		pixels[i * 4 + 1] = 0;
		pixels[i * 4 + 2] = 0;
		pixels[i * 4 + 3] = 255;
		i++;
	}
}

int	transform_to_channel(double v)
{
	if (v < 0.0)
		v = 0.0;
	if (v > 1.0)
		v = 1.0;
	return ((int)(v * 255.0));
}

uint32_t	get_color_from_vec3(t_vec3 *vec)
{
	uint32_t	res;

	res = transform_to_channel(vec->x) << 24 | transform_to_channel(vec->y) << 16 | transform_to_channel(vec->z) << 8 | 255;
	return (res);
}

t_hit	miss(void)
{
	t_hit	hit;

	hit.hit_distance = -1.0;
	return (hit);
}

t_hit	closest_hit(t_data *data, t_ray *ray, double distance, int ind)
{
	t_hit	hit;
	t_vec3	origin;

	hit.hit_distance = distance;
	hit.object_index = ind;
	origin = \
	subtract(ray->ray_origin, create_vec3_arr(data->spheres[ind].cords));
	hit.world_position = add(origin, scale(ray->ray_direction, distance));
	hit.world_normal = normalize(hit.world_position);
	hit.world_position = \
	add(hit.world_normal, create_vec3_arr(data->spheres[ind].cords));
	return (hit);
}

// (bx^2 + by^2 + bz^2)t^2 + (2(axbxzx + aybyzy))

t_hit	ray_trace(t_data *data, t_ray *ray)
{
	int		i = 0;

	int 	ind = -1;
	double closest = MAXFLOAT;
	while (i < data->amount_of_spheres)
	{
		t_vec3	origin = subtract(ray->ray_origin, create_vec3_arr(data->spheres[i].cords));
		double a = dot_product(ray->ray_direction,  ray->ray_direction);
		double b = 2.0 * dot_product(ray->ray_direction, origin);
		double c = dot_product(origin, origin) - data->spheres[i].diameter * data->spheres[i].diameter / 4.0;

		double descriminent = b * b - 4.0 * a * c;
		if (descriminent < 0)
		{
			i++;
			continue ;
		}
		double t1 = (-b - sqrt(descriminent)) / (2.0 * a);
		if (t1 < closest)
		{
			closest = t1;
			ind = i;
		}
		i++;

	}
	if (ind == -1)
		return (miss());
	return (closest_hit(data, ray, closest, ind));
}

uint32_t	per_pixel(t_data *data, t_ray *ray, uint32_t x, uint32_t y)
{
	ray->ray_direction = get_direction_ray(data, ((double)x / \
	(double)data->image->width) * 2.0 - 1.0, (1.0 - (double)y / \
	(double)data->image->height) * 2.0 - 1.0);

	t_hit hit = ray_trace(data, ray);
	if (hit.hit_distance < 0)
		return (255);
	t_vec3 light_dir = normalize(add(hit.world_normal, create_vec3_arr(data->light.cords)));
	// light_dir = normalize(create_vec3(1.0, 1.0, 1.0));
	double d = max_double(dot_product(hit.world_normal, light_dir), 0.0);
	// dprintf(1, "%f  ", d);
	t_vec3 color = create_vec3_color_arr(data->spheres[hit.object_index].colors);
	color = scale(color, d);
	return (get_color_from_vec3(&color));
}


int	displaying(t_data *data)
{
	uint32_t	y;
	uint32_t	x;
	uint32_t	pixel;
	t_ray		ray;

	y = 0;
	ray.ray_origin = create_vec3_arr(data->camera.cords);
	while (y < data->image->height)
	{
		x = 0;
		while (x < data->image->width)
		{
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
