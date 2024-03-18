/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davmart2 <davmart2@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 09:41:35 by davmart2          #+#    #+#             */
/*   Updated: 2024/03/15 08:34:39 by davmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

char	*ft_clean_str(char *str)
{
	char	*newstr;
	char	*ptr;
	int		len;

	ptr = ft_strchr(str, '\n');
	if (!ptr)
	{
		newstr = NULL;
		return (ft_free(&str));
	}
	else
		len = (ptr - str) + 1;
	if (!str[len])
		return (ft_free(&str));
	newstr = ft_substr(str, len, ft_strlen(str) - len);
	ft_free(&str);
	if (!newstr)
		return (NULL);
	return (newstr);
}

char	*ft_new_line(char *str)
{
	char	*line;
	char	*ptr;
	int		len;

	ptr = ft_strchr(str, '\n');
	len = (ptr - str) + 1;
	line = ft_substr(str, 0, len);
	if (!line)
		return (NULL);
	return (line);
}

char	*ft_read_fd(int fd, char *str)
{
	int		readline;
	char	*buffer;

	readline = 1;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (ft_free(&str));
	buffer[0] = '\0';
	while (readline > 0 && !ft_strchr(buffer, '\n'))
	{
		readline = read (fd, buffer, BUFFER_SIZE);
		if (readline > 0)
		{
			buffer[readline] = '\0';
			str = ft_strjoin(str, buffer);
		}
	}
	free(buffer);
	if (readline == -1)
		return (ft_free(&str));
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str = NULL;
	char		*buferline;

	if (fd < 0)
		return (NULL);
	if ((str && !ft_strchr(str, '\n')) || !str)
		str = ft_read_fd(fd, str);
	if (!str)
		return (NULL);
	buferline = ft_new_line(str);
	if (!buferline)
		return (ft_free(&str));
	str = ft_clean_str(str);
	return (buferline);
}
/*
int	main(void)
{
	char	*line;
	int		i;
	int		fd1;

	fd1 = open("test.txt", O_RDONLY);
	if (fd1 < 0)
	{
		perror("Error al abrir el archivo");
		return (1);
	}
	i = 1;
	while (1)
	{
		line = get_next_line(fd1);
		if (line == NULL)
			break;
		printf("line [%02d]: %s", i, line);
		free(line);
		i++;
	}
	close(fd1);
	return (0);
}*/
