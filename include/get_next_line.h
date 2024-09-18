/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:05:04 by obrittne          #+#    #+#             */
/*   Updated: 2024/09/18 14:41:04 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include "minirt.h"

char	*get_next_line(int fd, int *finished);
char	*solve_get_next(char *str, char *buffer, int fd, int *finished);
char	*allocate(char *str);
char	*strjoins(char *first, char *second, char *str);
size_t	get_ind_of_n_len(char *str, int l);
char	*help_delete_25_lines(char *str, char *out, char *second, \
size_t len1);


#endif