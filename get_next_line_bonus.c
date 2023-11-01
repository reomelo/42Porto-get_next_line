/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:23:23 by riolivei          #+#    #+#             */
/*   Updated: 2022/11/14 19:01:37 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*new_line(char *str)
{
	int		i;
	int		j;
	char	*string;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	string = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!string)
		return (NULL);
	i++;
	j = 0;
	while (str[i])
		string[j++] = str[i++];
	string[j] = '\0';
	free(str);
	return (string);
}

char	*get_content(char *str)
{
	int		i;
	char	*string;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	string = (char *)malloc(sizeof(char) * (i + 2));
	if (!string)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		string[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		string[i] = str[i];
		i++;
	}
	string[i] = '\0';
	return (string);
}

char	*read_line(int fd, char *str)
{
	char	*buff;
	int		count;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	count = 1;
	while (!ft_strchr(str, '\n') && count != 0)
	{
		count = read(fd, buff, BUFFER_SIZE);
		if (count == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[count] = '\0';
		str = ft_strjoin(str, buff);
	}
	free(buff);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str[FOPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX)
		return (NULL);
	str[fd] = read_line(fd, str[fd]);
	if (!str[fd])
		return (NULL);
	line = get_content(str[fd]);
	str[fd] = new_line(str[fd]);
	return (line);
}

/* #include <fcntl.h>
int	main(void)
{
	char	*line;
	int		i;
	int		fd1;
	int		fd2;
	int		fd3;

	fd1 = open("test.txt", O_RDONLY);
	fd2 = open("test1.txt", O_RDONLY);
	fd3 = open("test2.txt", O_RDONLY);
	i = 1;
	while (i < 9)
	{
		line = get_next_line(fd1);
		printf("line [%02d]: %s\n", i, line);
		free(line);
		line = get_next_line(fd2);
		printf("line [%02d]: %s\n", i, line);
		free(line);
		line = get_next_line(fd3);
		printf("line [%02d]: %s\n", i, line);
		free(line);
		printf("-----------------------------------
		-------------------------------------------");
		i++;
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
} */
