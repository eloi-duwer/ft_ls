/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_entries_funcs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eduwer <eduwer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 19:10:13 by eduwer            #+#    #+#             */
/*   Updated: 2021/01/21 20:20:16 by eduwer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

bool		is_folder(t_context *ctx, t_entry *entry)
{
	t_stat	stats;
	char	*str;

	if (stat(entry->path, &stats) == -1)
	{
		ft_asprintf(&str, "ft_ls: Can't stat file %s", entry->path);
		print_errno(ctx, str, false);
		free(str);
		return (false);
	}
	if ((stats.st_mode & S_IFMT) == FOLDER_MASK)
		return (true);
	return (false);
}

static char	*make_time_string(t_context *ctx, t_entry *entry)
{
	char	**splitted;
	char	*ret;

	if ((splitted = ft_strsplit(ctime(&entry->stats.st_mtime), ' ')) == NULL)
		return (NULL);
	if ((ctx->today > entry->stats.st_mtime && \
		ctx->today - entry->stats.st_mtime > 3600 * 24 * 30 * 6)
		|| entry->stats.st_mtime - ctx->today > 3600)
		ft_asprintf(&ret, "%.3s %2s %5.4s", \
			splitted[1], splitted[2], splitted[4]);
	else
		ft_asprintf(&ret, "%.3s %2s %.5s", \
			splitted[1], splitted[2], splitted[3]);
	ft_free_string_list(splitted);
	return (ret);
}

static void	add_soft_link(t_context *ctx, t_entry *entry)
{
	char	*str;

	if ((str = (char *)malloc(entry->stats.st_size + 1)) != NULL)
	{
		if (readlink(entry->path, str, entry->stats.st_size) == -1)
		{
			free(str);
			ft_asprintf(&str, "ft_ls: Can't read link %s", entry->path);
			print_errno(ctx, str, false);
			free(str);
			return ;
		}
		str[entry->stats.st_size] = '\0';
		ft_printf(" -> %s", str);
		free(str);
	}
	else
		print_errno(ctx, "ft_ls: Can't malloc", false);
}

void		print_entry(t_context *ctx, t_entry *entry, int max_len)
{
	char		right_string[11];
	t_passwd	*user_name;
	t_group		*group_name;
	char		*time_string;

	if (ctx->long_format == true)
	{
		make_rights_string(entry, right_string);
		user_name = getpwuid(entry->stats.st_uid);
		if (user_name == NULL)
			print_errno(ctx, "ft_ls: Can't get username infos", true);
		group_name = getgrgid(entry->stats.st_gid);
		if (group_name == NULL)
			print_errno(ctx, "ft_ls: Can't get group infos", true);
		time_string = make_time_string(ctx, entry);
		ft_printf("%s %d %s %s %*d %s %s", right_string, \
			entry->stats.st_nlink, user_name->pw_name, group_name->gr_name, \
			max_len, entry->stats.st_size, time_string, entry->filename);
		if (right_string[0] == 'l')
			add_soft_link(ctx, entry);
		ft_printf("\n");
		free(time_string);
	}
	else
		ft_printf("%s  ", entry->filename);
}

int			sum_entries_infos(t_context *ctx, t_entry *entry, \
	bool only_files, int *out_max_size)
{
	char	*buf;
	int		len;
	int		nb_blocks;

	*out_max_size = 0;
	nb_blocks = 0;
	while (entry != NULL)
	{
		if (!only_files || !is_folder(ctx, entry))
		{
			if ((len = ft_asprintf(&buf, "%ld", entry->stats.st_size)) \
				> *out_max_size)
				*out_max_size = len;
			free(buf);
			nb_blocks += entry->stats.st_blocks;
		}
		entry = entry->next;
	}
	return (nb_blocks);
}
