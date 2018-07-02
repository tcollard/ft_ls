/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcollard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 11:22:36 by tcollard          #+#    #+#             */
/*   Updated: 2018/05/31 18:06:26 by tcollard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <grp.h>
# include <pwd.h>
# include <time.h>
# include <dirent.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/acl.h>
# include <sys/xattr.h>
# include "../libft/includes/libft.h"

typedef struct		s_argv
{
	char			*name;
	struct s_argv	*next;
}					t_argv;

typedef struct		s_info
{
	char			name[PATH_MAX];
	char			full_path[PATH_MAX];
	char			*user;
	char			*grp;
	char			*time;
	char			lnk_path[PATH_MAX];
	unsigned char	type;
	off_t			size;
	long int		i_time;
	mode_t			mode;
	nlink_t			link;
	quad_t			blocks;
	dev_t			rdev;
	struct s_info	*next;
	struct s_info	*prev;
}					t_info;

typedef struct		s_padding
{
	int				link;
	int				user;
	int				grp;
	int				size;
	int				total;
}					t_padding;

int					init_option(int option[11], char *argv, int *x);
int					check_if_lnk(char *path);
void				init_lst(t_info **lst);
int					dispatch(char *path, int option[11]);
void				recursive(t_info **lst, char *path, int option[11]);
void				in_recursive(char *path, int option[11]);

void				get_path(char *tmp, char *path, struct dirent *data);
void				get_link_files(char *path, int option[11]);
void				fill_struct(struct stat buf, t_info *lst, int option[11]);
int					fill_lstruct(t_info *lst, char *path, int option[11]);
void				info_file(char *path, t_info **lst, unsigned char type,
					int option[11]);
void				del_lst(t_info **lst);

int					display(t_info **lst, int option[11]);
void				display_multi_arg(t_info **lst, int option[11]);
int					display_all(t_info *lst, int option[11]);
void				display_info(t_info *lst, t_padding pad, int option[11]);
void				fill_padding(t_info *lst, t_padding *pad);
void				init_padding(t_padding *pad);
void				padding_multi(t_info **lst, t_padding *pad, int option[11]);
unsigned char		style(struct stat buf);

void				add_mode(t_info *lst, char *str);
void				fill_display(t_info *lst, char *str, t_padding pad,
					int option[11]);

void				sort_rev(t_info **lst);
void				sort_clean_hide(t_info **lst);
void				sort_time(t_info **lst);
void				sort_size(t_info **lst);
void				sort_alpha(t_info **lst, t_info **new, int option[11]);
t_info				*sort_multi_arg(int i, char **argv, int option[11],
					int stop);
t_info				*sort(t_info *lst_fold, t_info *lst_no_fold,
					int option[11]);

int					lst_length(t_info **lst);
void				ft_error(int type, char *files, int err_value);
void				add_error(t_info **lst, char *path);
void				display_error(t_info **lst);
#endif
