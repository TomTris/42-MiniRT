/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:52:27 by obrittne          #+#    #+#             */
/*   Updated: 2024/09/19 15:14:42 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	ft_hook_keys(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
}

void	change_image_size_hook(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if ((uint32_t)data->mlx->width != data->image->width || \
	data->image->height != (uint32_t)data->mlx->height)
	{
		if (!mlx_resize_image(data->image, data->mlx->width, data->mlx->height))
			return (display_error_message("Couldnt resize"), \
			mlx_close_window(data->mlx));
		data->displayed = 0;
	}
	if (!data->displayed)
	{
		data->displayed = 1;
		make_image_black(data->image);
		if (!displaying(data))
			return (display_error_message("Error while displaying"), \
			mlx_close_window(data->mlx));
	}
}
