/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabeel <knabeel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:24:39 by knabeel           #+#    #+#             */
/*   Updated: 2022/10/03 20:04:27 by knabeel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// this function to get the first line
char	*ft_get_line(char *save)
{
	int		i;
	char	*s;

	i = 0;
	if (!save[i])
		return (NULL);
	while (save[i] != '\0' && save[i] != '\n') // to know how many sapce to allocate to the first line in the mempry
		i++;
	s = (char *) malloc(sizeof(char) * (i + 2)); // here we allocate to it a space in the memory the 2 is for \n and '\0'
	if (!s)
		return (NULL);
	i = 0; // notice here 
	while (save[i] && save[i] != '\n') // this time to copy
	{
		s[i] = save[i];
		i++;
	}
	if (save[i] == '\n') // to know where is the end of the first line
	{
		s[i] = save[i];
		i++;
	}
	s[i] = '\0'; // here we will put /0 to the i see the step before this
	return (s);
}

// this to get the next line 
char	*ft_skip(char *save)
{
	int		i;
	int		c;
	char	*new_buffer;

	i = 0;
	while (save[i] != '\0' && save[i] != '\n') // to get the first line
		i++;
	if (save[i] == '\0')
	{
		free (save);
		return (NULL);
	}
	new_buffer = (char *)malloc(sizeof(char) * (ft_strlen(save) - i + 1)); // we will subtract the save which is the first line and the second line with the first line, first+second - first = second
	if (!new_buffer)
	{
		return (NULL);
	}
	i++;
	c = 0;
	while (save[i] != '\0')
			new_buffer[c++] = save[i++]; // i now in the second line so the newbuffer willl copy from the second line
	new_buffer[c] = '\0';
	free (save); // no need for save now
	return (new_buffer); // it will be the static
}

char	*ft_read_and_save(int fd, char *save) // fd means out txt, save is the static
{
	char	*buff; // its empty it is where we will save what we will read
	int		read_bytes; // how many charachters the read function read.
	
	//printf("%s\n", save);
	buff = malloc((BUFFER_SIZE + 2) * sizeof(char)); 
	if (!buff)
		return (NULL);
	read_bytes = 1; // should be 1 because if it was zero thats mean there is nothing to read and we choese number 1 cuz it just makes sence
	while (!ft_strchr(save, '\n') && read_bytes != 0) // as we see it is an and condition which mean if one of them becomes false the loop will end. for ex: I will use get next line once, the output should be "red", buffersize is 1 it will move 4 times will stop in the /n red\n, the first condition is now false be cause !strchr \n, it does = \n the other condition is still true because we are not in the end of the file, but the loop will end cuz it is "&&"" condition  
	{
		read_bytes = read(fd, buff, BUFFER_SIZE); // read will read the fd, how it will move? the buffer_size will control this, inside the buff we will save what we read. what is the retrun value? it is an integer which is how maany characters we have been read, which will be the read-bytes.
		if (read_bytes == -1) // if it was a -1 means if there is an error or something free buff and retrun null.
		{
			free(buff);
			return (NULL);
		}
		buff[read_bytes] = '\0'; // this to tell the buff where to stop
		//  printf("%s\n", save);
		save = ft_strjoin (save, buff);
		//printf("%s\n", save);
	}
	free (buff); // it is important to free the buff you can see printf after and before free buff
	//printf("%s\n", save);
	return (save);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save; // so static char means it will save everything in it until the end of the program, for example; if I call get next line two times save will save what happen in the first get next line. 

	if (fd < 0 || BUFFER_SIZE <= 0) // if file d is empty or the buffer size is zero that means no buffer size then how it will read what inside the file discrepter, so it is important that the buffer size be > 0. 
		return (0);
	save = ft_read_and_save(fd, save); //this function will read everything in the file d expect if the buffer_size was less thr how many chracters in the file decrpter in this case it will stop when there is a /n  
	if (!save)
	{
		return (0);
	}
	line = ft_get_line (save);
	save = ft_skip (save);
	return (line);
}

// int main(void)
// {	
// 	char	*temp;
// 	int	fd;
// 	fd = open("ex.txt", O_RDONLY);
// 	while(1)
// 	{
// 		temp = get_next_line(fd);
// 		if (!temp)
// 		break ;
// 		printf("%s", temp);
// 		 free(temp);
// 	}
// 	// temp = get_next_line(fd);
// 	//temp = get_next_line(fd);
// 	//  free(temp);
// 	// printf("%s", temp);
// 	return (0);
// }