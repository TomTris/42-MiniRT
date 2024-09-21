/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:52:27 by obrittne          #+#    #+#             */
/*   Updated: 2024/09/21 18:01:26 by obrittne         ###   ########.fr       */
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

// (bx^2 + by^2 + bz^2)t^2 + (2(axbxzx + aybyzy))

uint32_t	per_pixel(t_data *data, uint32_t x, uint32_t y)
{
	double		x_val;
	double		y_val;
	t_vec3		vec;
	uint32_t	pixel;

	x_val = ((double)x / (double)data->image->width);
	y_val = (1.0 - (double)y / (double)data->image->height);
	pixel = 255;
	
	vec = get_direction_ray(data, x_val * 2.0 - 1.0, y_val * 2.0 - 1.0);

	double a = dot_product(vec, vec);
	double b = 2.0 * dot_product(vec, create_vec3_arr(data->camera.cords));
	double c = dot_product(create_vec3_arr(data->camera.cords), create_vec3_arr(data->camera.cords)) - data->spheres->diameter * data->spheres->diameter / 4.0;

	double descriminent = b * b - 4.0 * a * c;
	if (descriminent < 0)
	{
		return (pixel);
	}
	// double t0 = (-b + sqrt(descriminent)) / (2.0 * a);
	double t1 = (-b - sqrt(descriminent)) / (2.0 * a);
	// dprintf(1, "%f\n", descriminent);
	// t_vec3 hit_pos1 = add(data->camera.vec3, scale(vec, t0));
	// t_vec3 scaled = scale(vec, t1);
	t_vec3 hit_pos2 = add(create_vec3_arr(data->camera.cords), scale(vec, t1));
	// dprintf(1, "%f--%f--%f\n", scaled.x, scaled.y, scaled.z);
	// dprintf(1, "%f--%f--%f\n", data->camera.vec3.x, data->camera.vec3.y, data->camera.vec3.z);
	t_vec3 normal = normalize(hit_pos2);
	// dprintf(1, "%f--%f--%f\n\n\n", hit_pos2.x, hit_pos2.y, hit_pos2.z);
	// normal = normalize(add(scale(normal, 0.5), create_vec3(0.5, 0.5, 0.5)));
	t_vec3 color = create_vec3(1, 0, 1);
	t_vec3 light_dir = normalize(add(hit_pos2, create_vec3_arr(data->light.cords)));
	// light_dir = normalize(create_vec3(1.0, 1.0, 1.0));
	double d = max_double(dot_product(normal, light_dir), 0.0);
	// dprintf(1, "%f  ", d);
	color = scale(color, d);
	pixel = get_color_from_vec3(&color);
	return (pixel);
}

int	displaying(t_data *data)
{
	uint32_t	y;
	uint32_t	x;
	uint32_t	pixel;

	y = 0;
	while (y < data->image->height)
	{
		x = 0;
		while (x < data->image->width)
		{
			pixel = per_pixel(data, x, y);
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
