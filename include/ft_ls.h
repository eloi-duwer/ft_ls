#ifndef __FT_LS_H__
# define __FT_LS_H__
# include <libft.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <dirent.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# define false 0
# define true 1
# define FILE_MASK S_IFREG
# define FOLDER_MASK S_IFDIR
# define LINK_MASK S_IFLNK
# define CHARDEVICE_MASK S_IFCHR
# define BLOCKDEVICE_MASK S_IFBLK
# define SOCKET_MASK S_IFSOCK
# define PIPE_MASK S_IFIFO

typedef char			t_bool;
typedef	struct stat		t_stat;
typedef struct dirent	t_dirent;
typedef struct passwd	t_passwd;
typedef struct group	t_group;

typedef	struct	s_entry {
	struct s_entry	*next;
	struct s_entry	*prev;
	struct s_entry	*files;
	t_stat			stats;
	char			*path;
	char			*filename;
	int				max_length;
	int				nb_blocks;
	t_bool			sorted;
}				t_entry;

typedef struct	s_context {
	int				(*comp_func)(t_entry *one, t_entry *two);
	t_entry			*entries;
	time_t			today;
	int				return_code;
	t_bool			sort_reverse;
	t_bool			all;
	t_bool			recursive;
	t_bool			long_format;
	t_bool			only_one_folder;
	t_bool			printed_something;
}				t_context;

void	print_error(char *str, t_bool should_exit);
void	print_error_details(char *str, char *details, t_bool should_exit);
void	print_errno(t_context *ctx, char *str, t_bool should_exit);
void	parse_subargs(t_context *ctx, char *args);
void	parse_args(int ac, char **av, t_context *ctx);
t_bool	add_entry_beginning(t_context *ctx, t_entry **first_entry, \
			char *path, char *filename);
t_bool	add_entry_end(t_context *ctx, t_entry **first_entry, \
			char *path, char *filename);
t_bool	remove_entry(t_entry **first_entry, t_entry *entry);
void	swap_adjacent_entries(t_entry **first_entry, t_entry *one, \
			t_entry *two);
int		sort_by_name(t_entry *one, t_entry *two);
int		sort_by_date(t_entry *one, t_entry *two);
void	sort_entries(t_context *ctx, t_entry **first_entry);
t_bool	file_type(t_entry *entry, unsigned int mask);
void	print_folders(t_context *ctx);
void	first_pass_print_files(t_context *ctx);
void	make_rights_string(t_entry *entry, char *str);
char	*join_filename(char *path, char *name);

# endif
