/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_vec3_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:40:26 by obrittne          #+#    #+#             */
/*   Updated: 2024/09/22 12:42:05 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_vec3	create_vec3_color_arr(int *arr)
{
	t_vec3	res;

	res.x = (double)arr[0] / 255.0;
	res.y = (double)arr[1] / 255.0;
	res.z = (double)arr[2] / 255.0;
	return (res);
}
