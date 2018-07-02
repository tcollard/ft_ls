/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 13:54:07 by tcollard          #+#    #+#             */
/*   Updated: 2018/05/31 12:46:32 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	display_error(t_info **lst)
{
	struct stat	buf;
	t_info		*tmp;

	tmp = *lst;
	while (tmp)
	{
		lstat(tmp->name, &buf);
		ft_error(1, tmp->name, 0);
		tmp = tmp->next;
	}
	del_lst(lst);
}

void	add_error(t_info **lst, char *path)
{
	t_info	*tmp;

	tmp = NULL;
	if (!(tmp = (t_info *)malloc(sizeof(t_info))))
		return ;
	ft_bzero((void *)(tmp->name), PATH_MAX);
	ft_strcat(tmp->name, path);
	sort_alpha(lst, &tmp, 0);
}

void	ft_error(int type, char *files, int err_value)
{
	int		i;

	err_value = 0;
	i = 0;
	if (type == 1)
	{
		write(2, "ls: ", 4);
		write(2, &files[i], ft_strlen(&files[i]));
		perror(" ");
	}
	else if (type == 2)
	{
		write(2, "\nls: ", 5);
		write(2, files, ft_strlen(files));
		perror(" ");
	}
	else if (type == 3)
	{
		write(2, "ls: illegal option -- ", 22);
		write(2, files, 1);
		write(2, "\nusage: ls [-RSadfglrtu] [file ...]\n", 36);
	}
}
