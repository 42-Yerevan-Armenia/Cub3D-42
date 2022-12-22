/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arakhurs <arakhurs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:23:10 by arakhurs          #+#    #+#             */
/*   Updated: 2022/12/08 20:24:29 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub.h"

char	*mywhile(int fd, char *sline)
{
	char	buffer[4];
	long	rsize;

	while (1)
	{	
		rsize = read(fd, buffer, 1);
		buffer[rsize] = '\0';
		if (rsize == -1)
			return (0);
		if (!sline)
			sline = ft_strdup(buffer);
		else
			sline = ft_strjoin(sline, buffer);
		if (ft_strchr(buffer, '\n') || rsize == 0)
			break ;
	}
	return (sline);
}

char	*get_next_line(int fd)
{
	static char	*sline;
	char		*until_n;
	char		*tline;
	long		slinelen;

	sline = mywhile(fd, sline);
	if (!sline)
		return (NULL);
	slinelen = ft_strlen(sline) - ft_strlen(ft_strchr(sline, '\n')) + 1;
	until_n = ft_substr(sline, 0, slinelen);
	tline = sline;
	sline = ft_substr(sline, slinelen, ft_strlen(sline));
	free(tline);
	return (until_n);
}
