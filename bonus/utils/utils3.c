/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:11:42 by obrittne          #+#    #+#             */
/*   Updated: 2024/09/25 19:47:42 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	copy_all_stuff(void *to, void *from, int len)
{
	char	*char_from;
	char	*char_to;
	int		i;

	if (!from)
		return ;
	char_from = (char *)from;
	char_to = (char *)to;
	i = 0;
	while (i < len)
	{
		char_to[i] = char_from[i];
		i++;
	}
}
