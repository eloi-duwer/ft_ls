#include <ft_ls.h>

t_bool		file_type(t_entry *entry, unsigned int mask)
{
	if ((entry->stats.st_mode & S_IFMT) == mask)
		return (true);
	return (false);
}

static char	find_type_file(t_entry *entry)
{
	if (file_type(entry, FOLDER_MASK))
		return ('d');
	else if (file_type(entry, CHARDEVICE_MASK))
		return ('c');
	else if (file_type(entry, BLOCKDEVICE_MASK))
		return ('b');
	else if (file_type(entry, SOCKET_MASK))
		return ('s');
	else if (file_type(entry, PIPE_MASK))
		return ('p');
	else if (file_type(entry, LINK_MASK))
		return ('l');
	else
		return ('-');
}

void	make_rights_string(t_entry *entry, char *str)
{
	ft_memset(str, '-', 10);
	str[0] = find_type_file(entry);
	if (entry->stats.st_mode & S_IRUSR)
		str[1] = 'r';
	if (entry->stats.st_mode & S_IWUSR)
		str[2] = 'w';
	if (entry->stats.st_mode & S_IXUSR)
		str[3] = 'x';
	if (entry->stats.st_mode & S_IRGRP)
		str[4] = 'r';
	if (entry->stats.st_mode & S_IWGRP)
		str[5] = 'w';
	if (entry->stats.st_mode & S_IXGRP)
		str[6] = 'x';
	if (entry->stats.st_mode & S_IROTH)
		str[7] = 'r';
	if (entry->stats.st_mode & S_IWOTH)
		str[8] = 'w';
	if (entry->stats.st_mode & S_IXOTH)
		str[9] = 'x';
	str[10] = '\0';
}

char	*join_filename(char *path, char *name)
{
	size_t	lengths[2];
	char 	*ret;
	t_bool	add_slash;

	lengths[0] = ft_strlen(path);
	lengths[1] = ft_strlen(name);
	add_slash = false;
	if (path[lengths[0] - 1] != '/')
		add_slash = true;
	if ((ret = (char *)ft_memalloc(lengths[0] + add_slash + lengths[1] + 1)) == NULL)
		return NULL;
	ft_memcpy(ret, path, lengths[0]);
	if (add_slash == true)
		ret[lengths[0]] = '/';
	ft_memcpy(&(ret[lengths[0] + add_slash]), name, lengths[1]);
	return (ret);
}
