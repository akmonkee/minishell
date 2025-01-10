/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:18:50 by msisto            #+#    #+#             */
/*   Updated: 2025/01/10 12:52:49 by marvin           ###   ########.fr       */
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
# define SYMBOLS "<|>&;()"

/*cmd type ids*/

# define EXEC 1
# define REDIR 2
# define PIPE 3
# define LIST 4
# define BACK 5

# define MAXARGS 10

extern int		g_code_exit;

/*cmd structs*/

typedef struct s_cmd
{
	int				type;
	int				or;
	int				pipe;
	char			*cmd;
	struct s_cmd	*next;
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
	struct cmd	*cmd;
	char		*file;
	char		*efile;
	int			mode;
	int			fd;
}	t_redircmd;

typedef struct s_pipecmd
{
	int			type;
	struct cmd	*left;
	struct cmd	*right;
}	t_pipecmd;

typedef struct s_listcmd
{
	int			type;
	struct cmd	*left;
	struct cmd	*right;
}	t_listcmd;

typedef struct s_backcmd
{
	int			type;
	struct cmd	*cmd;
}	t_back_cmd;

typedef struct s_data
{
	char		*temp;
	char		*temp2;
	int			i;
	int			j;
	char		*env_var;
	char		*env_name;
	int			pipe;
	int			pipe_1;
	int			or;
	int			or_1;
	int			quote;
	int			dquote;
}				t_data;

typedef struct s_data2
{
	char		**arg;
	char		*t1;
	char		*t2;
	int			i;
}				t_data2;

typedef struct s_main
{
	t_cmd	*lcmd;
	char	*input;
	char	**env;
	int		print;
	int		npipe;
	int		ncmd;
	int		in;
	int		out;
}				t_main;

//ARGS
//env_expander.c
char		*env_expander(t_main *main, t_cmd *cur, t_data data);
//env_redirections.c
char		**env_redir(char **matrix);
//take_args.c
void		rm_prefix(t_main *main, t_cmd *cur, int i);
char		**take_args(t_main *main, t_cmd *cur, char *str);
void		start_shell(char **envp);

//BUILTIN
//builtin commands
int			builtin_pwd(void);
int			builtin_exit(t_main *main, char *cmd, int i, int j);
int			builtin_env(t_main *main, t_cmd *cur);
//builtin_utils.c
int			looking_for_env(t_main *main, char *cmd);
int			control_bt(char *input, char **envp);
char		*pick_env(t_main *main, char *cmd);

//EXECUTE
//exec_functions.c
void		execute_cmd(t_execcmd *cmd);
void		redircmd(t_redircmd *cmd);
void		pipecmd(t_pipecmd *cmd);
void		listcmd(t_listcmd *cmd);
void		backcmd(t_back_cmd *cmd);
//exec.c
void		execute(t_cmd *cmd);

//PANIC
//panic.c
int			malloc_p(char **m);
int			file_p(char *file, int cmd);

//UTILS
//freeable.c
void		free_all(t_main *main);
int			free_matrix(char **matrix);
int			free_str(char *str);
//ft_split.c
char		**ft_split(char const *s, char c);
//ft_strjoin.c
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strjoin12f(char *s1, char *s2);
char		*ft_strjoin1f(char *s1, char *s2);
char		*ft_strjoin2f(char *s1, char *s2);
//ft_substr.c
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strdup(void);
//utils_bt.c
char		*get_path(void);
int			ft_matrixlen(char **matrix);
//utils_get_args.c
void		word_count(int *word, char *str, int *i, char c);
char		*substr_extract(char *str, int *i, char c);
char		*substr_extract2(char *str, int *i);
void		which_utils(char *str, int *i, int *word, char **matrix);
//utils.c
int			ft_strchr(char *comp, char s);
size_t		ft_strlen(char	*s);
void		*ft_memset(void *b, int c, size_t len);
void		ft_putstr_fd(char *s, int fd);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
//utils2.c
int			ft_isdigit(int c);
int			ft_atoi(const char *s);
int			skip_space(int i, char *str);

#endif
