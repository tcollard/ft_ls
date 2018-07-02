/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 15:04:22 by tcollard          #+#    #+#             */
/*   Updated: 2018/06/01 13:19:49 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		display_multi_arg(t_info **lst, int option[11])
{
	t_info		*tmp;
	t_padding	pad;

	tmp = *lst;
	padding_multi(lst, &pad, option);
	while (tmp != NULL)
	{
		if (tmp->type != DT_DIR || (tmp->type == DT_LNK && option[0] == 1)
			|| option[9] == 1)
			(option[0] == 1) ? display_info(tmp, pad, option) :
				ft_printf("%s\n", tmp->name);
		else
		{
			if (tmp->prev == NULL)
				ft_printf("%s:\n", tmp->name);
			else
				ft_printf("\n%s:\n", tmp->name);
			dispatch(tmp->name, option);
		}
		tmp = tmp->next;
	}
}

int			display(t_info **lst, int option[11])
{
	int		ret;
	t_info	*tmp;

	ret = 0;
	if (!(*lst))
		return (ret);
	(option[10] == 1) ? sort_size(lst) : 0;
	(option[4] == 1) ? sort_time(lst) : 0;
	(option[3] == 1) ? sort_rev(lst) : 0;
	tmp = *lst;
	if (option[0] == 1)
		ret = display_all(tmp, option);
	else
		while (tmp != NULL)
		{
			(tmp->type == DT_DIR) ? ret += 1 : 0;
			ft_printf("%s\n", tmp->name);
			tmp = tmp->next;
		}
	return (ret);
}

int			display_all(t_info *lst, int option[11])
{
	t_info		*tmp;
	t_padding	pad;
	int			ret;

	ret = 0;
	tmp = lst;
	init_padding(&pad);
	while (tmp != NULL)
	{
		fill_padding(tmp, &pad);
		tmp = tmp->next;
	}
	if (lst != NULL && option[5] == 1)
		ft_printf("total %i\n", pad.total);
	while (lst != NULL)
	{
		(lst->type == 4) ? ret += 1 : 0;
		display_info(lst, pad, option);
		lst = lst->next;
	}
	return (ret);
}

static void	display_g(t_info *lst, char *str)
{
	if (lst->type == DT_LNK)
		ft_printf(str, lst->link, lst->grp, lst->size, lst->time,
		lst->name, lst->lnk_path);
	else if (lst->type == DT_BLK || lst->type == DT_CHR)
		ft_printf(str, lst->link, lst->grp, major(lst->rdev),
		minor(lst->rdev), lst->time, lst->name);
	else
		ft_printf(str, lst->link, lst->grp, lst->size, lst->time,
		lst->name);
}

void		display_info(t_info *lst, t_padding pad, int option[11])
{
	char	str[80];
	int		i;

	i = 1;
	ft_bzero((void *)str, 80);
	while (i < 10)
		str[i++] = '-';
	add_mode(lst, str);
	fill_display(lst, str, pad, option);
	if (option[8] == 1)
		display_g(lst, str);
	else if (lst->type == DT_LNK)
		ft_printf(str, lst->link, lst->user, lst->grp, lst->size, lst->time,
		lst->name, lst->lnk_path);
	else if (lst->type == DT_BLK || lst->type == DT_CHR)
		ft_printf(str, lst->link, lst->user, lst->grp, major(lst->rdev),
		minor(lst->rdev), lst->time, lst->name);
	else
		ft_printf(str, lst->link, lst->user, lst->grp, lst->size, lst->time,
		lst->name);
}
