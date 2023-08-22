/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabeel <knabeel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 18:40:18 by knabeel           #+#    #+#             */
/*   Updated: 2022/10/03 19:16:08 by knabeel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_line(char *save)
{
	int		i;
	char	*s;

	i = 0;
	if (!save[i])
		return (NULL);
	while (save[i] != '\0' && save[i] != '\n')
		i++;
	s = (char *) malloc(sizeof(char) * (i + 2));
	if (!s)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		s[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		s[i] = save[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_skip(char *save)
{
	int		i;
	int		c;
	char	*new_buffer;

	i = 0;
	while (save[i] != '\0' && save[i] != '\n')
		i++;
	if (save[i] == '\0')
	{
		free (save);
		return (NULL);
	}
	new_buffer = (char *)malloc(sizeof(char) * (ft_strlen(save) - i + 1));
	if (!new_buffer)
	{
		return (NULL);
	}
	i++;
	c = 0;
	while (save[i] != '\0')
			new_buffer[c++] = save[i++];
	new_buffer[c] = '\0';
	free (save);
	return (new_buffer);
}

char	*ft_read_and_save(int fd, char *save)
{
	char	*buff;
	int		read_bytes;

	buff = malloc((BUFFER_SIZE + 2) * sizeof(char));
	if (!buff)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(save, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[read_bytes] = '\0';
		save = ft_strjoin (save, buff);
	}
	free (buff);
	return (save);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save[4096]; // what is this?

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save[fd] = ft_read_and_save (fd, save[fd]);
	if (!save[fd])
	{
		return (NULL);
	}
	line = ft_get_line (save[fd]);
	save[fd] = ft_skip(save[fd]);
	return (line);
}

// int main()
// {
// 	char *line;
// 	char *line2;
// 	char *line3;
// 	int fd;
// 	int fd2;
// 	int fd3;
// 	int i;

// 	i = 1;
// 	fd = open("1.txt", O_RDONLY);
// 	fd2 = open("2.txt", O_RDONLY);
// 	fd3 = open("3.txt", O_RDONLY);
// 	// while(i < 4)
// 	// {
// 	// 	line = get_next_line(fd);
// 	// 	printf("line [%d]: %s\n", i, line);
// 	// 	free(line);
// 	// 	line = get_next_line(fd2);
// 	// 	printf("line [%d]: %s\n", i, line);
// 	// 	free(line);
// 	// 	line = get_next_line(fd3);
// 	// 	printf("line [%d]: %s\n", i, line);
// 	// 	free(line);
// 	// 	i++;
// 	// }
//     line = get_next_line(fd);
//     line = get_next_line(fd);
//     line2 = get_next_line(fd2);
//     line2 = get_next_line(fd2);
// 	line3 = get_next_line(fd3);
//     line3 = get_next_line(fd3);
//     printf(" fd; %s", line);
//     printf(" fd2; %s", line2);
// 	printf(" fd3; %s", line3);

// 	close(fd);
// 	close(fd2);
// 	close(fd3);
// 	return (0);
// }