/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsheryl <bsheryl@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 15:49:57 by bsheryl           #+#    #+#             */
/*   Updated: 2021/10/18 13:43:51 by bsheryl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_str(int fd, char *str, char *buff)
{
	int	bytes;

	bytes = 1;
	while (!ft_strchr(str, '\n') && bytes != 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(buff);
			return (0);
		}
		buff[bytes] = '\0';
		if (!str)
			str = ft_substr(buff, 0, bytes);
		else
			str = ft_strjoin(str, buff);
	}
	free(buff);
	return (str);
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

char	*ft_get_begin_line(char *str)
{
	int		begin;
	char	*ret;

	begin = 0;
	while (str[begin] && str[begin] != '\n')
		begin++;
	begin++;
	ret = ft_substr(str, begin, ft_strlen(str));
	free(str);
	return (ret);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buff;
	static char	*str;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (0);
	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (0);
	str = ft_read_str(fd, str, buff);
	if (!str || str[0] == '\0')
	{
		free(str);
		str = 0;
		return (NULL);
	}
	line = ft_get_line(str);
	if (!line || line[0] == '\0')
	{
		free(line);
		return (0);
	}
	str = ft_get_begin_line(str);
	return (line);
}
