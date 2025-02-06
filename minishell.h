/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:18:50 by msisto            #+#    #+#             */
/*   Updated: 2025/02/05 13:25:23 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <termcap.h>
# include <termios.h>

# define IMG "......,,:::,,..,;+++;;:,,:::;;;+;;:,.,,:::,,.............,,:::," \
",..,;+++;;:,,:::;;;+;;:,.,,:::,,......\n....,+****+;;::;;;;;;;;;;;;;;;;;;;;:" \
":;++****+,.........,+****+;;::;;;;;;;;;;;;;;;;;;;;::;++****+,....\n....;**++" \
";;;;;;;;;;;;;;;;;;;;;;;;;;;;:::;;+**,.........;**++;;;;;;;;;;;;;;;;;;;;;;;;;" \
";;;:::;;+**,....\n....,;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;::::,,........,;;" \
";;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;::::,,...\n..,;;;;;;;;;;;;;;;;;;;;;;;;;;;;" \
";;;;;;;:;:;;;;;::.....,;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;:;:;;;;;::..\n.:;;" \
";;;;;+?S%+;;;;;;;;;;;;;;;;;;;;;;;;%%?;;;;;;;:,..:;;;;;;;+?S%+;;;;;;;;;;;;;;;" \
";;;;;;;;;%%?;;;;;;;:,\n:;;;;;;;;;***;;;;;;;;;;;;;;;;;;;;;;;;;+**;;;;;;;;:.:;" \
";;;;;;;;***;;;;;;;;;;;;;;;;;;;;;;;;;+**;;;;;;;;:\n;;;;+++;;;;;;;;;;;;;;;;;;;" \
";;;;;;;;;;;;;;;;;;++;;;;.;;;;+++;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;++;;;;" \
"\n:;;;++*+++******************++++++++++++++;++;;;;:.:;;;++*+++*************" \
"*****++++++++++++++;++;;;;:\n,:;;;;;;;+++++++++++****+*+++++++++++++++;;;;;;" \
";:..,:;;;;;;;+++++++++++****+*+++++++++++++++;;;;;;;:.\n..,;;;;;;;;;;;;;;;;;" \
";;;;;;;;;;;;;;;;;;;;;;;;;;;:.....,;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;" \
";;:..\n....,:;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;:,........,:;;;;;;;;;;;;" \
";;;;;;;;;;;;;;;;;;;;;;;;;;;:,...\n.....:+;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;" \
";;,...........:+;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;,.....\n.....,:;;;;++++" \
"+++++++++++++++++++++++;;;;;:,...........,:;;;;+++++++++++++++++++++++++++;;" \
";;;:,.....\n.......,:;;;;:,,,,,,::::::::::::,,,:;+++;;:...............,:;;;;" \
":,,,,,,::::::::::::,,,:;+++;;:.......\n"

# define WHITE_SPACE " \t\r\n\v"
# define SYMBOLS "<|>"
# define BUFFER_SIZE 1

/*cmd type ids*/

# define EXEC 1
# define REDIR 2
# define PIPE 3

# define MAXARGS 10

/*cmd structs*/

typedef struct s_cmd
{
	int	type;
}	t_cmd;

typedef struct s_execcmd
{
	int		type;
	char	*argv[MAXARGS];
	char	*eargv[MAXARGS];
}	t_execcmd;

typedef struct s_redircmd
{
	int			type;
	t_cmd		*cmd;
	char		*file;
	int			here_doc;
	int			mode;
	int			fd;
}	t_redircmd;

typedef struct s_pipecmd
{
	int			type;
	t_cmd	*left;
	t_cmd	*right;
}	t_pipecmd;

//main
void	parse_exe(char *input, char **envp);
void	start_shell(char **envp);
//utils/freecmd
void	freepipe(t_cmd *cmd);
void	freecmd(t_cmd *cmd);
//utils/signal_utils
void	handle_sigquit(int sig);
void	handle_sigint(int sig);
//utils/quote_utils
int		parse_squote(char *s, char *es);
int		check_singleq(char *q);
char	*quote_man(char *q, char *eq);
//utils/utils
char	*name_extractor(char *q, char *eq);
int		ft_strchr(char *comp, char s);
size_t	ft_strlen(char	*s);
void	*ft_memset(void *b, int c, size_t len);
//parse
int		peek(char **ps, char *es, char *toks);
int		gettoken(char **ps, char *es, char **q, char **eq);
t_cmd	*parseline(char **ps, char *es);
t_cmd	*parsecmd(char *s);
//parse quotes
char	single_quote(char *s, char *es);
//parse pipe
t_cmd	*parsepipe(char **ps, char *es);
//parseexec
t_cmd	*execcmd();
t_cmd	*parseexec(char **ps, char *es);
//parseredirs
t_cmd	*redircmd(t_cmd *subcmd, char *file, int here_doc, int mode);
t_cmd	*parseredirs(t_cmd *cmd, char **ps, char *es);
//nulterminate
t_cmd	*nulterminate(t_cmd *cmd);
//runcmd/fullexecmd
char	*ft_strjoin(char *path, char *cmd);
void	mtxs_free(char **mtx);
char	*cmd_check(char **path, char *command);
void	ft_execute_command(char **command, char **envp);
//runcmd/pathfinder
char	*path_ex(char *string, int ex_len, int start);
int		path_count(char *string, char c);
char	**ft_split(char *string, char c, int index, int start);
char	*ft_strnstr(const char *s, const char *to_find, size_t len);
char	**path_finder(char **envp);
//runcmd/runcmd
void	doc_cmd(t_cmd *cmd, char **envp);
void	runcmd(t_cmd *cmd, char **envp);
//runcmd/runpipe
int		fork1();
void	runpipe(t_cmd *cmd, char **envp);
//runcmd/runredir
int		eof_checker(char *line, char *rule);
void	here_doc(t_redircmd *rcmd, char *rule);
void	runredir(t_cmd *cmd, char **envp);
//get_next_line
char	*gnl_strjoin(char *line, char *buf);
char	*str_clear(char *buf);
char	*get_next_line(int fd, int i2);
void	ft_in_array(char *buf);
int		ft_strlen_g(const char *str);
char	*print_out(char *ret);
char	*update_ret(char *ret);
char	*ft_strchr_g(const char *s, int c);
char	*get_line(int fd, char *ret);
char	*return_fun(char *output);

#endif
