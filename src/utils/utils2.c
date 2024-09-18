/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:41:07 by obrittne          #+#    #+#             */
/*   Updated: 2024/09/18 15:17:18 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minirt.h"

void	delete_useless_spaces(char *str)
{
	int	ptr1;
	int	ptr2;

	ptr1 = 0;
	ptr2 = 0;
	while (str[ptr1])
	{
		if (is_white_space(str[ptr1]) && !(ptr2 == 0 || str[ptr2 - 1] == ' ' || \
		str[ptr2 - 1] == ','))
		{
			str[ptr2] = ' ';
			ptr2++;
		}
		else if (!is_white_space(str[ptr1]))
		{
			str[ptr2] = str[ptr1];
			ptr2++;
		}
		ptr1++;
	}
	if (ptr2 != 0 && is_white_space(str[ptr2 - 1]))
		str[ptr2 - 1] = 0;
	else
		str[ptr2] = 0;
}

void	display_error_message(char *str)
{
	write(2, "Error\n", 6);
	write(2, str, str_len(str));
	write(2, "\n", 1);
}

int	str_compare(char *str1, char *str2)
{
	int	ptr;

	ptr = 0;
	while (1)
	{
		if (!str1[ptr] && !str2[ptr])
			break ;
		if (str1[ptr] != str2[ptr])
			return (str1[ptr] - str2[ptr]);
		ptr++;
	}
	return (0);
}

int	len2d_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		i++;
	}
	return (i);
}

int	get_pos_of_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}