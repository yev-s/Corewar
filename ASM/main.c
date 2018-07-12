#include "asm.h"

void	ft_error(char *str)
{
	ft_printf("%s\n", str);
	exit(0);
}

// void		ft_syntax(int i, int j)
// {
// 	ft_printf("Syntax error at [%.3d:%.3d]\n", i, j);
// 	exit(0);
// }

t_asm			*init_asmb(void)
{
	t_asm		*s;

	if (!(s = (t_asm*)malloc(sizeof(t_asm))))
		ft_error("Error [init_asmb()]: memory was not allocated");
	// ft_bzero(s->prog_name, PROG_NAME_LENGTH + 1);
	// ft_bzero(s->comment, COMMENT_LENGTH + 1);
	s->prog_name = NULL;
	s->comment = NULL;
	s->file_name = NULL;
	s->flag_a = 0;
	s->prog_size = 0;
	s->new_fd = 0;
	s->command = NULL;
	return (s);
}



/*
** 3 functions for checking if it's line is
** bot_name_line, bot_comment_line or comment_line
*/

char		is_bot_name(char *s)
{
	if (!s)
		return (0);
	while (*s && (*s == ' ' || *s == '\t'))
		s++;
	if (ft_strncmp(s, NAME_CMD, ft_strlen(NAME_CMD)) == 0)
		return (1);
	return (0);
}

char		is_bot_comment(char *s)
{
	if (!s)
		return (0);
	while (*s && (*s == ' ' || *s == '\t'))
		s++;
	if (ft_strncmp(s, COMMENT_CMD, ft_strlen(COMMENT_CMD)) == 0)
		return (1);
	return (0);
}

char		is_comment(char *s)
{
	if (!s)
		return (0);
	while (*s && (*s == ' ' || *s == '\t'))
		s++;
	return ((*s == ';' || *s == '#' || *s == '\0') ? 1 : 0);
}











/*
** 2 functions for getting bot name.
** first function writes to name string in main structure called asmb.
** second check if it's valid name string and send this string int pieces.
*/

// char	copy_to_dst(char *dst, char *src, int *j)
// {
// 	static int i = 0;

// 	while (i < PROG_NAME_LENGTH && src[*j] && src[*j] != '\"')
// 	{
// 		dst[i] = src[*j];
// 		i++;
// 		(*j)++;
// 	}
// 	(i == PROG_NAME_LENGTH && src[*j] != '\"') ? ft_error("Error") : 0;
// 	return ((src[*j] == '\"') ? 1 : 0);
// }

// void	add_name(char *dst, char **src, int fd, char *flag)
// {
// 	int		j;

// 	(*flag & 1) ? ft_error("Error") : (*flag = *flag | 1);
// 	j = ft_strstr(*src, NAME_CMD_STRING) - *src + ft_strlen(NAME_CMD_STRING);
// 	while ((*src)[j] && ((*src)[j] == ' ' || (*src)[j] == '\t'))
// 		j++;
// 	((*src)[j] != '\"') ? ft_error("Error") : j++;
// 	while (*src && !copy_to_dst(dst, *src, &j))
// 	{
// 		j = 0;
// 		ft_strdel(src);
// 		get_next_line(fd, src);
// 	}
// 	(!*src) ? ft_error("Error") : 0;
// 	((*src)[j] != '\"') ? ft_error("Error") : j++;
// 	while ((*src)[j] && ((*src)[j] == ' ' || (*src)[j] == '\t'))
// 		j++;
// 	if ((*src)[j] != '#' && (*src)[j] != ';' && (*src)[j] != '\0')
// 		ft_error("Error");
// }

// void	add_comment(char *dst, char **src, int fd, int *i)
// {
// 	int j;

// 	(*flag & 2) ? ft_error("Error") : (*flag = *flag | 2);
// 	j = ft_strstr(*src, COMMENT_CMD_STRING) - *src + ft_strlen(COMMENT_CMD_STRING);
// 	((*src)[j] != '\"') ? ft_error("Error") : j++;
// 	while (*src && !copy_to_dst(dst, *src, &j))
// 	{
// 		j = 0;
// 		ft_strdel(src);
// 		get_next_line(fd, src);
// 	}
// 	(!*src) ? ft_error("Error") : 0;
// 	((*src)[j] != '\"') ? ft_error("Error") : j++;
// 	while ((*src)[j] && ((*src)[j] == ' ' || (*src)[j] == '\t'))
// 		j++;
// 	if ((*src)[j] != '#' && (*src)[j] != ';' && (*src)[j] != '\0')
// 		ft_error("Error");
// }


// while (*src && !copy_to_dst(new_line, *src, &j))
	// {
	// 	j = 0;
	// 	ft_strdel(src);
	// 	get_next_line(fd, src);
	// }





/*
** needle_cmd -> (NAME_CMD / COMMENT_CMD)
** needle_size -> (PROG_NAME_LENGTH / COMMENT_LENGTH)
*/

// char	*copy_to_dst(char **src, int needle_size, char fd)
// {
// 	char	*new_line;
// 	int		i; // for new_line
// 	int		j; // for src

// 	new_line = (char*)malloc(needle_size + 1);
// 	ft_bzero(new_line, needle_size + 1);
// 	i = 0;
// 	j = ft_strchr(*src, '\"') - *src;
// 	while (*src)
// 	{
// 		*src = ft_strjoinfree(*src, "\n", 1); // free *str
// 		while (i < needle_size && (*src)[j] && (*src)[j] != '\"')
// 			new_line[i++] = (*src)[j++];
// 		if ((*src)[j] == '\"')
// 			break ;
// 		((*src)[j] != '\0') ? ft_error("Error") : (j = 0);
// 		ft_strdel(src);
// 		get_next_line(fd, src);
// 	}
// 	(!*src || (*src)[j] != '\"') ? ft_error("Error") : j++;
// 	while ((*src)[j] && ((*src)[j] == ' ' || (*src)[j] == '\t'))
// 		j++;
// 	if ((*src)[j] != '#' && (*src)[j] != ';' && (*src)[j] != '\0')
// 		ft_error("Error");
// 	return (new_line);
// }

char	*copy_to_dst(char **src, int needle_size, char fd, int *j)
{
	char	*new_line;
	int		i; // for new_line.

	new_line = (char*)malloc(needle_size + 1);
	ft_bzero(new_line, needle_size + 1);
	i = 0;
	*j = ft_strchr(*src, '\"') - *src + 1; // index in src after bracket(").
	while (*src)
	{
		*src = ft_strjoinfree(*src, "\n", 1); // free *str
		while (i < needle_size && (*src)[*j] && (*src)[*j] != '\"')
			new_line[i++] = (*src)[(*j)++];
		if ((*src)[*j] == '\"')
			break ;
		else if ((*src)[*j] != '\0')
			ft_error("Error");
		j = 0;
		ft_strdel(src);
		get_next_line(fd, src);
	}
	return (new_line);
}

char	*get_str(char **src, char *needle_cmd, int needle_size, char fd)
{
	char	*new_line;
	int		j;

	j = ft_strstr(*src, needle_cmd) - *src + ft_strlen(needle_cmd); // index in src after needle_cmd.
	while ((*src)[j] && ((*src)[j] == ' ' || (*src)[j] == '\t'))    // skip spaces and tabs.
		j++;
	((*src)[j] != '\"') ? ft_error("Error") : j++;                  // check bracket.
	new_line = copy_to_dst(src, needle_size, fd, &j);               // copy string between brackets.
	(!*src || (*src)[j] != '\"') ? ft_error("Error") : j++;         // check bracket.
	while ((*src)[j] && ((*src)[j] == ' ' || (*src)[j] == '\t'))    // skip spaces and tabs.
		j++;
	if ((*src)[j] != '#' && (*src)[j] != ';' && (*src)[j] != '\n')  // check the comment. \n because i have added to this string this character.
		ft_error("Error");
	return (new_line);
}

void	get_name_and_comment(t_asm *asmb)
{
	char	*line;
	char	flag; // 1 bit is for name, and 2 bit - for comment.

	line = 0;
	flag = 0;
	while (get_next_line(asmb->fd, &line) > 0)
	{
		if (is_bot_name(line))
		{
			(flag & 1) ? ft_error("Error") : (flag = flag | 1);
			asmb->prog_name = get_str(&line, NAME_CMD, PROG_NAME_LENGTH, asmb->fd);
		}
		else if (is_bot_comment(line))
		{
			(flag & 2) ? ft_error("Error") : (flag = flag | 2);
			asmb->comment = get_str(&line, COMMENT_CMD, COMMENT_LENGTH, asmb->fd);
		}
		else if (!is_comment(line))
			ft_error("Error");
		ft_strdel(&line);
		if (flag == 3)
			break ;
	}
	(flag != 3) ? ft_error("Error\n") : 0;
}

// void	get_commands(int fd, t_asm *asmb)
// {

// }

void		parsing(t_asm *asmb)
{
	get_name_and_comment(asmb);
	// get_commands(asmb, i);
}

void	check_argvs(t_asm *asmb, char **av, int ac)
{
	while (--ac > 0)
	{
		if (ft_strequ(av[ac], "-a"))
			asmb->flag_a = 1;
		else if (!asmb->file_name)
			asmb->file_name = ft_strdup(av[ac]);
	}
}


int		main(int ac, char **av)
{
	t_asm	*asmb;

	if (ac == 1)
		ft_putstr("Usage: ./asm [-a] <sourcefile.s>\n\
    -a : Instead of creating a .cor file, outputs a \
stripped and annotated version of the code to the standard output\n");
	else
	{
		asmb = init_asmb();
		check_argvs(asmb, av, ac);
		if (!asmb->file_name ||
			(asmb->fd = open(asmb->file_name, O_RDONLY)) < 0 ||
			read(asmb->fd, 0, 0) == -1)
			ft_error(ERR_FILE);
		parsing(asmb);

		printf("prog_name = %s\n", asmb->prog_name);
		printf("prog_comment = %s\n", asmb->comment);

		// (asmb->flag_a) ? show_bot(asmb) : create_binary(asmb);
		// close(asmb->fd);
	}
	return (0);
}
