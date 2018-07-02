/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 15:06:47 by tcollard          #+#    #+#             */
/*   Updated: 2018/05/31 17:01:22 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		sort_rev(t_info **lst)
{
	t_info	*tmp1;
	t_info	*tmp2;
	t_info	*tmp;

	if (!(*lst) || (*lst)->next == NULL)
		return ;
	tmp1 = (*lst);
	tmp2 = tmp1->next;
	(*lst)->next = NULL;
	while (tmp2 != NULL)
	{
		tmp1->prev = tmp2;
		tmp = tmp2->next;
		tmp2->next = tmp1;
		tmp1 = tmp2;
		tmp2 = tmp;
	}
	tmp1->prev = NULL;
	*lst = tmp1;
}

static void	little_swap(t_info **tmp, t_info **new)
{
	(*new)->next = *tmp;
	(*tmp)->prev->next = *new;
	(*new)->prev = (*tmp)->prev;
	(*tmp)->prev = *new;
}

static void	add_elem(t_info **lst, t_info **new, int option[11])
{
	t_info	*tmp;

	tmp = *lst;
	if (option[7] == 2)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = *new;
		(*new)->prev = tmp;
	}
	else
	{
		(*new)->next = *lst;
		(*lst)->prev = *new;
		*lst = *new;
	}
}

void		sort_alpha(t_info **lst, t_info **new, int option[11])
{
	t_info	*tmp;

	tmp = *lst;
	if (*lst == NULL)
		*lst = *new;
	else if (option[7] > 0)
		return (add_elem(lst, new, option));
	else if (ft_strcmp(tmp->name, (*new)->name) >= 0)
	{
		(*new)->next = tmp;
		tmp->prev = *new;
		*lst = *new;
	}
	else
	{
		while (tmp->next != NULL && ft_strcmp(tmp->name, (*new)->name) < 0)
			tmp = tmp->next;
		if (ft_strcmp(tmp->name, (*new)->name) >= 0)
			little_swap(&tmp, new);
		else
		{
			tmp->next = *new;
			(*new)->prev = tmp;
		}
	}
}
