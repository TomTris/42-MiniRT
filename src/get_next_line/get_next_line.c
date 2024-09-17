/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:09:32 by obrittne          #+#    #+#             */
/*   Updated: 2024/09/17 17:18:48 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	str[BUFFER_SIZE + 1];
	char		buffer[BUFFER_SIZE + 1];
	static int	first = 1;
	size_t		bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bytes = 0;
	while (bytes <= BUFFER_SIZE)
		buffer[bytes++] = 0;
	bytes = 0;
	if (first)
	{
		while (bytes <= BUFFER_SIZE)
			str[bytes++] = 0;
		first = 0;
	}
	bytes = get_ind_of_n_len(str, 0);
	if (bytes)
		return (allocate(str));
	return (solve(str, buffer, fd));
}

// int main()
// {
// 	int fd = open("test", O_RDONLY);
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// }
// CC=gcc
// CFLAGS= -Wall -Werror -Wextra
// NAME=get_next_line.a
// SRCS= get_next_line.c get_next_line_utils.c
// OBJS=$(SRCS:.c=.o)
// SRCS_BONUS= get_next_line_utils_bonus.c get_next_line_bonus.c
// OBJS_BONUS=$(SRCS_BONUS:.c=.o)

// all: $(NAME)

// $(NAME): $(OBJS)
// 	ar rcs ${NAME} ${OBJS}

// bonus: all

// clean:
// 	rm -f $(OBJS) $(OBJS_BONUS)

// fclean: clean
// 	rm -f $(NAME)

// re: fclean all

// .PHONY: all clean fclean re