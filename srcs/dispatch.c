/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 15:03:55 by tcollard          #+#    #+#             */
/*   Updated: 2018/06/01 13:39:43 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int				dispatch(char *path, int option[11])
{
	t_info			*lst;
	struct stat		buf;
	struct stat		buf_tmp;

	lst = NULL;
	stat(path, &buf_tmp);
	lstat(path, &buf);
	if (((S_IFMT & buf.st_mode) != S_IFDIR && ft_strcmp(path, "./") != 0 &&
	ft_strcmp(path, "../") != 0 && ft_strcmp(path, ".") != 0 && ft_strcmp(path,
	"..") != 0 && option[1] == 0) || option[9] == 1 || ((style(buf) == 10 ||
	style(buf_tmp) == 10) && option[1] == 1 && option[0] == 1))
		if (style(buf) == 10 && option[0] == 0 && style(buf_tmp) == 4)
			get_link_files(path, option);
		else
		{
			info_file(path, &lst, style(buf), option);
			display(&lst, option);
			del_lst(&lst);
		}
	else
	{
		option[5] = 1;
		in_recursive(path, option);
	}
	return (1);
}

unsigned char	style(struct stat buf)
{
	unsigned char	type;

	type = 0;
	(S_IFIFO == (S_IFMT & buf.st_mode)) ? type = 1 : 0;
	(S_IFCHR == (S_IFMT & buf.st_mode)) ? type = 2 : 0;
	(S_IFDIR == (S_IFMT & buf.st_mode)) ? type = 4 : 0;
	(S_IFBLK == (S_IFMT & buf.st_mode)) ? type = 6 : 0;
	(S_IFREG == (S_IFMT & buf.st_mode)) ? type = 8 : 0;
	(S_IFLNK == (S_IFMT & buf.st_mode)) ? type = 10 : 0;
	(S_IFSOCK == (S_IFMT & buf.st_mode)) ? type = 12 : 0;
	return (type);
}

void			recursive(t_info **lst, char *path, int option[11])
{
	size_t	i;
	char	path_save[PATH_MAX];
	char	path_tmp[PATH_MAX];
	t_info	*tmp;

	i = 0;
	tmp = *lst;
	ft_strcpy(path_save, path);
	while (tmp != NULL)
	{
		if (tmp->type == 4)
		{
			option[5] = 1;
			ft_strcpy(path_tmp, path_save);
			if (tmp->type == 4 && ft_strcmp(tmp->name, ".") != 0 &&
					ft_strcmp(tmp->name, "..") != 0)
			{
				ft_strcat(path_tmp, "/");
				ft_strcat(path_tmp, tmp->name);
				ft_printf("\n%s:\n", path_tmp);
				in_recursive(path_tmp, option);
			}
		}
		tmp = tmp->next;
	}
}

void			get_path(char *tmp, char *path, struct dirent *data)
{
	ft_bzero((void *)tmp, PATH_MAX);
	tmp = ft_strcat(tmp, path);
	tmp = ft_strcat(tmp, "/");
	tmp = ft_strcat(tmp, data->d_name);
}

void			in_recursive(char *path, int option[11])
{
	DIR				*dirp;
	struct dirent	*data;
	t_info			*lst;
	int				ret;
	char			tmp[PATH_MAX];

	ret = 0;
	lst = NULL;
	data = NULL;
	errno = 0;
	if (!(dirp = opendir(path)))
		return (ft_error(1, path, errno));
	while ((data = readdir(dirp)))
	{
		get_path(tmp, path, data);
		info_file(tmp, &lst, data->d_type, option);
	}
	ret += display(&lst, option);
	(ret != 0 && option[1] == 1) ? recursive(&lst, path, option) : 0;
	(closedir(dirp) == -1) ? (perror("ls:")) : 0;
	del_lst(&lst);
}
