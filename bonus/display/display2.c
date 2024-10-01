/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:34:46 by qdo               #+#    #+#             */
/*   Updated: 2024/10/01 18:01:10 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_vec3	per_pixel(t_data *data, t_ray *ray, uint32_t x, uint32_t y)
{
	t_hit	hit;
	t_vec3	color;

	hit.checkers = 0;
	ray->ray_direction = get_direction_ray(data, ((double)x / \
	(double)data->image->width) * 2.0 - 1.0, (1.0 - (double)y / \
	(double)data->image->height) * 2.0 - 1.0);
	ray_trace(data, ray, &hit);
	if (hit.found == 0)
		return (create_vec3(0, 0, 0));
	color = calculate_light(data, ray, &hit);
	return (color);
}

void	*displaying(void *input)
{
	t_data		*data;
	uint32_t	y;
	uint32_t	x;
	t_vec3		pixel;
	t_ray		ray;
	int			*index;
	int			ind;

	data = ((t_input *)input)->data;
	index = (((t_input *)input)->ind);
	ind = *index;
	free(index);
	free(input);
	// ProfilerStart("profile_output.prof");
	y = 0;
	while (y < data->image->height)
	{
		x = 0;
		while (x < data->image->width)
		{
			if (x % AMOUNT_OF_THREADS == ind)
			{
				ray.ray_origin = data->camera.vec3_cords;
				pixel = per_pixel(data, &ray, x, y);
				// data->pixels[y * data->image->width + x] = add(data->pixels[y * data->image->width + x], pixel);
				// mlx_put_pixel(data->image, x, y, get_color_from_vec3(scale(data->pixels[y * data->image->width + x], 1.0 / (double)t)));
				mlx_put_pixel(data->image, x, y, get_color_from_vec3(pixel));
			}
			x++;
		}
		y++;
	}

	// ProfilerStop();
	return (NULL);
}

void	display(t_data *data)
{

	data->texture = mlx_load_png("./textures/football.png");
	// if (!data->texture)
	// dprintf(1, "%f\n", data->planes->dist);
	// exit(1);
	// dprintf(1, "asdasd");
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
