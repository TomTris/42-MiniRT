/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:58:53 by obrittne          #+#    #+#             */
/*   Updated: 2024/09/18 14:40:52 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

char	*help_delete_25_lines(char *str, char *out, char *second, size_t len1)
{
	size_t	it;

	it = 0;
	if (second == NULL && len1 == 0)
	{
		if (str)
			free(str);
		return (out);
	}
	else if (second == NULL && len1 == 123)
	{
		if (*str == 0)
		{
			free(str);
			return (NULL);
		}
		return (out);
	}
	while (second[len1] && len1 < BUFFER_SIZE)
		str[it++] = second[len1++];
	while (str[it] && it < BUFFER_SIZE)
		str[it++] = 0;
	return (NULL);
}

size_t	get_ind_of_n_len(char *str, int l)
{
	size_t	it;

	it = 0;
	if (!l)
	{
		while (1)
		{
			if (!str[it])
				break ;
			if (str[it] == '\n')
				return (it + 1);
			it++;
		}
		return (0);
	}
	while (str[it])
		it++;
	return (it);
}

char	*strjoins(char *first, char *second, char *str)
{
	char	*out;
	size_t	len1;
	size_t	len2;
	size_t	it;

	len1 = get_ind_of_n_len(first, 1);
	len2 = get_ind_of_n_len(second, 0);
	if (!len2)
		len2 = get_ind_of_n_len(second, 1);
	out = malloc((len2 + len1 + 1) * sizeof(char));
	if (!out)
		return (help_delete_25_lines(first, NULL, NULL, 0));
	len1 = 0;
	it = 0;
	while (first[len1])
		out[it++] = first[len1++];
	len1 = 0;
	while (len1 < len2)
		out[it++] = second[len1++];
	out[it] = 0;
	help_delete_25_lines(str, NULL, second, len1);
	return (help_delete_25_lines(first, out, NULL, 0));
}

char	*allocate(char *str)
{
	size_t	len;
	char	*out;
	size_t	len1;
	size_t	pointer;
	size_t	other;

	len = get_ind_of_n_len(str, 0);
	len1 = get_ind_of_n_len(str, 1);
	if (!len)
		len = len1;
	out = malloc((len + 1) * sizeof(char));
	if (!out)
		return (NULL);
	pointer = 0;
	while (pointer++ < len)
		out[pointer - 1] = str[pointer - 1];
	out[pointer - 1] = 0;
	other = 0;
	pointer--;
	while (pointer < len1)
		str[other++] = str[pointer++];
	while (other < BUFFER_SIZE)
		str[other++] = 0;
	return (out);
}

char	*solve_get_next(char *str, char *buffer, int fd, int *finished)
{
	char	*out;
	ssize_t	bytes;
	size_t	t;
	size_t	ind;

	out = allocate(str);
	if (!out)
		return (NULL);
	while (1)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
			return (help_delete_25_lines(out, NULL, NULL, 0));
		ind = get_ind_of_n_len(buffer, 0);
		out = strjoins(out, buffer, str);
		if (!out)
			return (NULL);
		t = 0;
		while (t < BUFFER_SIZE)
			buffer[t++] = 0;
		if (ind || (!ind && bytes != BUFFER_SIZE))
			break ;
	}
	*finished = 1;
	return (help_delete_25_lines(out, out, NULL, 123));
}
