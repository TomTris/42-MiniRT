/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:52:27 by obrittne          #+#    #+#             */
/*   Updated: 2024/09/19 15:14:05 by obrittne         ###   ########.fr       */
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

uint32_t	per_pixel(mlx_image_t *image, uint32_t x, uint32_t y)
{
	double		x_val;
	double		y_val;
	uint32_t	pixel;

	x_val = (double)x / (double)image->width;
	y_val = (double)y / (double)image->height;
	pixel = 255;
	pixel |= (uint32_t)(x_val * 255.0) << 24 | (uint32_t)(y_val * 255.0) << 16;

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
			pixel = per_pixel(data->image, x, y);
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
