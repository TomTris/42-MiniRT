/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:52:27 by obrittne          #+#    #+#             */
/*   Updated: 2024/09/29 20:59:02 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

long long	current_time_in_ms(void)
{
	struct timeval	time_now;
	long long		milliseconds;

	gettimeofday(&time_now, NULL);
	milliseconds = (long long) time_now.tv_sec * 1000 \
		+ time_now.tv_usec / 1000;
	return (milliseconds);
}

void	ft_hook_keys(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
}

void	change_image_size_hook(void *param)
{
	t_data		*data;
	long long	start;

	data = (t_data *)param;
	if ((uint32_t)data->mlx->width != data->image->width || \
	data->image->height != (uint32_t)data->mlx->height)
	{
		if (!mlx_resize_image(data->image, data->mlx->width, \
				data->mlx->height))
			return (display_error_message("Couldnt resize"), \
			mlx_close_window(data->mlx));
		data->displayed = 0;
	}
	if (!data->displayed)
	{
		start = current_time_in_ms();
		data->displayed = 1;
		if (!create_the_threads(data))
			return (display_error_message("Error while displaying"), \
			mlx_close_window(data->mlx));
		dprintf(1, "%lli\n", current_time_in_ms() - start);
	}
}
