/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:41:04 by obrittne          #+#    #+#             */
/*   Updated: 2024/09/17 19:41:05 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minirt.h"

int	str_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}


int	ends_with(char *main, char *sub)
{
	int	len1;
	int	len2;

	len1 = str_len(main);
	len2 = str_len(sub);
	if (len2 > len1)
		return (0);
	main += len1 - len2;
	while (len2 > 0)
	{
		if (main[len2 - 1] != sub[len2 - 1])
			return (0);
		len2--;
	}
	return (1);
}

void	change_new_line(char *str)
{
	int	len;

	len = str_len(str);
	if (str[len - 1] == '\n')
		str[len - 1] = 0;
}

void	change_app(char *str, char from, char to)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == from)
			str[i] = to;
		i++;
	}
}

int	is_white_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 12))
		return (1);
	return (0);
}
