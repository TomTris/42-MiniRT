/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:52:27 by obrittne          #+#    #+#             */
/*   Updated: 2024/09/24 13:07:14 by obrittne         ###   ########.fr       */
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
		hit->world_position = subtract(ray->ray_origin, hit->cords);
	}
}

void	handle_spheres(t_data *data, t_ray *ray, t_hit *hit)
{
	int		i;
	t_vec3	origin;

	i = -1;
	while (++i < data->amount_of_spheres)
	{
		origin = subtract(ray->ray_origin, data->spheres[i].vec3_cords);
		hit->vars_sp.a = dot_product(ray->ray_direction,  ray->ray_direction);
		hit->vars_sp.b = 2.0 * dot_product(ray->ray_direction, origin);
		hit->vars_sp.c = dot_product(origin, origin) - data->spheres[i].diameter * data->spheres[i].diameter / 4.0;
		hit->vars_sp.descriminent = hit->vars_sp.b * hit->vars_sp.b - 4.0 * hit->vars_sp.a * hit->vars_sp.c;
		if (hit->vars_sp.descriminent < 0)
			continue ;
		hit->vars_sp.t = (-hit->vars_sp.b - sqrt(hit->vars_sp.descriminent)) / (2.0 * hit->vars_sp.a);
		if (hit->vars_sp.t > 0.0 && hit->vars_sp.t < hit->hit_distance)
		{
			hit->hit_distance = hit->vars_sp.t;
			hit->found = 1;
			hit->color = data->spheres[i].vec3_color;
			hit->cords = data->spheres[i].vec3_cords;
			hit->type = 1;
		}
	}
}

double	get_factor(t_vec3 *norm, t_vec3	*point, t_vec3 *camera)
{
	t_var_sphere	vars;

	vars.d = dot_product(*norm, *point);
	vars.a = dot_product(*camera, *norm);
	vars.b = dot_product(*norm, *norm);
	vars.c = vars.d - vars.a;
	vars.t = vars.c / vars.b;
	if (vars.t < 0)
		return (1.0);
	return (-1.0);
}


void	handle_planes(t_data *data, t_ray *ray, t_hit *hit)
{
	int	i;

	i = -1;
	while (++i < data->amount_of_planes)
	{
		hit->vars_sp.d = dot_product(data->planes[i].vec3_cords, data->planes[i].vec3_norm);
		hit->vars_sp.a = dot_product(ray->ray_origin, data->planes[i].vec3_norm);
		hit->vars_sp.b = dot_product(ray->ray_direction, data->planes[i].vec3_norm);
		hit->vars_sp.c = hit->vars_sp.d - hit->vars_sp.a;
		if (hit->vars_sp.b == 0)
			continue ;
		hit->vars_sp.t = hit->vars_sp.c / hit->vars_sp.b;
		if (hit->vars_sp.t > 0.0 && hit->vars_sp.t < hit->hit_distance)
		{
			hit->hit_distance = hit->vars_sp.t;
			hit->found = 1;
			hit->color = data->planes[i].vec3_color;
			hit->cords = data->planes[i].vec3_cords;
			hit->type = 2;
			hit->normal = scale(data->planes[i].vec3_norm, get_factor(&data->planes[i].vec3_norm, &data->planes[i].vec3_cords, &ray->ray_origin));
		}
	}
}

void	handle_cylinders(t_data *data, t_ray *ray, t_hit *hit)
{
	int	i;

	i = -1;
	while (++i < data->amount_of_cylinders)
	{
		hit->vars_sp.d = scale(data->cylinders[i].vec3_norm, dot_product(ray->ray_direction, data->cylinders[i].vec3_norm));
		hit->vars_sp.a = dot_product();
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
	ray->ray_direction = get_direction_ray(data, ((double)x / \
	(double)data->image->width) * 2.0 - 1.0, (1.0 - (double)y / \
	(double)data->image->height) * 2.0 - 1.0);

	t_hit hit;
	ray_trace(data, ray, &hit);
	if (hit.found == 0)
		return (255);
	t_vec3 light_dir = normalize(add(hit.world_normal, create_vec3_arr(data->light.cords)));
	// light_dir = normalize(create_vec3(1.0, 1.0, 1.0));
	double d = max_double(dot_product(hit.world_normal, light_dir), 0.0);
	d *= data->light.ratio;
	// dprintf(1, "%f  ", d);
	t_vec3 obj_color = hit.color;
	t_vec3 color = multiply_vec3(obj_color, create_vec3_color_arr(data->light.colors));
	color = scale(color, d);


	
	t_vec3 ambient_color = create_vec3_color_arr(data->ambitient_light.colors);
    t_vec3 ambient_component = multiply_vec3(obj_color, ambient_color);
    ambient_component = scale(ambient_component, data->ambitient_light.ratio * data->light.ratio);

	t_vec3 final_color = add(color, ambient_component);
	// t_vec3 final_color = color;
	final_color = shrink_vec3(final_color, 0.0, 1.0);
	return (get_color_from_vec3(&final_color));
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
