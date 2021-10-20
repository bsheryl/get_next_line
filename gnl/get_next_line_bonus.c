/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsheryl <bsheryl@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 18:10:40 by bsheryl           #+#    #+#             */
/*   Updated: 2021/10/18 14:06:51 by bsheryl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_read_str(int fd, char **str, char *buff)
{
	int	bytes;

	bytes = 1;
	while (!ft_strchr(str[fd], '\n') && bytes != 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(buff);
			return (0);
		}
		buff[bytes] = '\0';
		if (!str[fd])
			str[fd] = ft_substr(buff, 0, bytes);
		else
			str[fd] = ft_strjoin(str[fd], buff);
	}
	free(buff);
	return (str[fd]);
}

char	*ft_get_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	line = ft_substr(str, 0, i);
	return (line);
}

char	*ft_get_begin_line(char **str, int fd)
{
	int		begin;
	char	*ret;

	begin = 0;
	while (str[fd][begin] && str[fd][begin] != '\n')
		begin++;
	if (!str[fd][begin])
	{
		free(str[fd]);
		return (0);
	}
	begin++;
	ret = ft_substr(str[fd], begin, ft_strlen(str[fd]));
	free(str[fd]);
	str[fd] = 0;
	return (ret);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buff;
	static char	*str[1024];

	if (fd < 0 || BUFFER_SIZE < 1)
		return (0);
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (0);
	str[fd] = ft_read_str(fd, str, buff);
	if (!str[fd] || str[fd][0] == '\0')
	{
		free(str[fd]);
		str[fd] = 0;
		return (0);
	}
	line = ft_get_line(str[fd]);
	if (line[0] == '\0')
	{
		free(line);
		line = 0;
		return (0);
	}
	str[fd] = ft_get_begin_line(str, fd);
	return (line);
}
