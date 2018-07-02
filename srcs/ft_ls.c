/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 12:19:05 by tcollard          #+#    #+#             */
/*   Updated: 2018/06/06 15:09:49 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int			main(int argc, char **argv)
{
	int		i;
	int		x;
	int		option[11];
	t_info	*lst;

	i = 0;
	x = 0;
	lst = NULL;
	while (i < 11)
		option[i++] = 0;
	i = 1;
	while (argv[i] && argv[i][0] == '-' && argv[i][1] != '\0' && x == 0)
		if ((x = init_option(option, argv[i], &i)) > 0)
			return (1);
	lst = sort_multi_arg(argc, argv, option, i);
	if (lst && argc != i + 1)
		display_multi_arg(&lst, option);
	else if (!lst && argc == i)
		dispatch(".", option);
	else if (!lst || (lst->name[0] == '-' && (S_IFDIR == (S_IFMT & lst->type))))
		return (1);
	else
		dispatch(lst->name, option);
	del_lst(&lst);
	return (0);
}

static void	info_arg(char *path, t_info **lst, unsigned char type,
		int option[11])
{
	int			i;
	t_info		*tmp;
	struct stat	buf;

	if (!(tmp = (t_info *)malloc(sizeof(t_info))))
		return ;
	tmp->time = NULL;
	ft_bzero((void *)(tmp->name), PATH_MAX);
	ft_strcat(tmp->name, path);
	tmp->type = type;
	i = 0;
	tmp->user = NULL;
	tmp->grp = NULL;
	(stat(path, &buf) == -1) ? i = fill_lstruct(tmp, path, option) :
		fill_struct(buf, tmp, option);
	tmp->next = NULL;
	tmp->prev = NULL;
	(i != -1) ? sort_alpha(lst, &tmp, option) : free(tmp);
}

t_info		*sort_multi_arg(int i, char **argv, int option[11], int stop)
{
	t_info		*lst_no_fold;
	t_info		*lst_fold;
	t_info		*lst_error;
	struct stat	buf;
	struct stat	buf_tmp;

	lst_no_fold = NULL;
	lst_fold = NULL;
	lst_error = NULL;
	while (--i >= stop)
	{
		stat(argv[i], &buf_tmp);
		(lstat(argv[i], &buf) == -1) ? add_error(&lst_error, argv[i]) : 0;
		if (S_IFDIR == (S_IFMT & buf.st_mode) || (S_IFLNK == (S_IFMT &
		buf.st_mode) && S_IFDIR == (S_IFMT & buf_tmp.st_mode) && option[0] == 0)
		|| option[9] == 1)
			info_arg(argv[i], &lst_fold, 0, option);
		else if (S_IFLNK == (S_IFMT & buf.st_mode))
			info_arg(argv[i], &lst_no_fold, 10, option);
		else
			info_arg(argv[i], &lst_no_fold, 0, option);
	}
	display_error(&lst_error);
	return (sort(lst_fold, lst_no_fold, option));
}

t_info		*sort(t_info *lst_fold, t_info *lst_no_fold, int option[11])
{
	t_info	*tmp;

	tmp = NULL;
	(option[10] == 1) ? sort_size(&lst_fold) : 0;
	(option[10] == 1) ? sort_size(&lst_no_fold) : 0;
	(option[4] == 1) ? sort_time(&lst_fold) : 0;
	(option[4] == 1) ? sort_time(&lst_no_fold) : 0;
	(option[3] == 1) ? sort_rev(&lst_fold) : 0;
	(option[3] == 1) ? sort_rev(&lst_no_fold) : 0;
	tmp = lst_no_fold;
	if (tmp != NULL && lst_fold != NULL)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = lst_fold;
		lst_fold->prev = tmp;
	}
	else if (tmp == NULL)
		return (lst_fold);
	return (lst_no_fold);
}
