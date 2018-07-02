/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 11:30:15 by tcollard          #+#    #+#             */
/*   Updated: 2018/05/31 18:18:33 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void	check_option(int option[11])
{
	if (option[7] == 1)
	{
		option[2] = 1;
		option[3] = 0;
		option[4] = 0;
	}
	(option[8] == 1) ? option[0] = 1 : 0;
	(option[10] == 1) ? option[4] = 0 : 0;
}

static void	add_option(int option[11], char *argv)
{
	(*argv == 'l') ? option[0] = 1 : 0;
	(*argv == 'R') ? option[1] = 1 : 0;
	(*argv == 'a') ? option[2] = 1 : 0;
	(*argv == 'r') ? option[3] = 1 : 0;
	(*argv == 't') ? option[4] = 1 : 0;
	(*argv == 'u') ? option[6] = 1 : 0;
	(*argv == 'f') ? option[7] = 1 : 0;
	(*argv == 'g') ? option[8] = 1 : 0;
	(*argv == 'd') ? option[9] = 1 : 0;
	(*argv == 'S') ? option[10] = 1 : 0;
}

int			init_option(int option[11], char *argv, int *x)
{
	char			*str;

	str = "ls: illegal option -- %c\nusage: ls [-Ralrt1] [file ...]\n";
	*x += 1;
	if (argv[1] == '\0' || (argv[1] == '-' && argv[2] == '\0'))
		return (-1);
	argv++;
	while (*argv)
	{
		add_option(option, argv);
		if (*argv != 'l' && *argv != 'R' && *argv != 'a' && *argv !=
		'r' && *argv != 't' && *argv != '1' && *argv != 'u' && *argv != 'f'
		&& *argv != 'g' && *argv != 'd' && *argv != 'S')
		{
			ft_error(3, &(*argv), 0);
			return (1);
		}
		argv++;
	}
	check_option(option);
	return (0);
}
