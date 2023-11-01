/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 16:13:15 by riolivei          #+#    #+#             */
/*   Updated: 2022/11/21 18:17:50 by riolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//remove a linha escrita da str
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

//obtem o conteudo da primeira linha
char	*get_content(char *str)
{
	int		i;
	char	*content;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	content = (char *)malloc(sizeof(char) * (i + 2));
	if (!content)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		content[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		content[i] = str[i];
		i++;
	}
	content[i] = '\0';
	return (content);
}

//le todo o conteudo e guarda no str
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
	static char	*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = read_line(fd, str);
	if (!str)
		return (NULL);
	line = get_content(str);
	str = new_line(str);
	return (line);
}

/* #include <stdio.h>
#include <fcntl.h>
int	main(void)
{
	char	*line;
	int		i;
	int		fd1;

	fd1 = open("test.txt", O_RDONLY);
	i = 1;
	while (i < 8)
	{
		line = get_next_line(fd1);
		printf("line [%d]: %s\n", i, line);
		free(line);

		i++;
	}
	close(fd1);
	return (0);
}
 */
