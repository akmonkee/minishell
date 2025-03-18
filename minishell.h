/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:18:50 by msisto            #+#    #+#             */
/*   Updated: 2025/03/18 11:39:48 by msisto           ###   ########.fr       */
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

extern int g_exit_code;

typedef struct s_mini
{
	char	**env;
}	t_mini;

/*cmd structs*/

typedef struct s_cmd
{
	int		type;
}	t_cmd;

typedef struct s_execcmd
{
	int		type;
	char	*argv[MAXARGS];
	char	*eargv[MAXARGS];
}	t_execcmd;

typedef struct s_redircmd
{
	int		type;
	t_cmd	*cmd;
	char	*file;
	int		here_doc;
	int		mode;
	int		fd;
}	t_redircmd;

typedef struct s_pipecmd
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_pipecmd;

//main
void	parse_exe(char *input, t_mini *mini);
void	start_shell(char **envp);
//utils/freecmd
void	freepipe(t_cmd *cmd);
void	freecmd(t_cmd *cmd);
//utils/signal_utils
void	ign(int sig);
void	signal_execve(int sig);
void	signal_handler(int sig);
//utils/quote_utils
int		parse_squote(char *s, char *es);
int		check_singleq(char *q);
char	*quote_man(char *q, char *eq);
//utils/utils
char	*name_extractor(char *q, char *eq);
int		ft_strchr(char *comp, char s);
size_t	ft_strlen(char	*s);
void	*ft_memset(void *b, int c, size_t len);
int		mtx_len(char **mtx);
//utils/utils_2
char	*var_ex(char *str, char c);
int		varcmp(char *str1, char *str2, int n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isdigit(int c);
int		ft_atoi(const char *s);
//parse
int		peek(char **ps, char *es, char *toks);
int		redir_check(char **s, char redir, int curr_ret);
int		gettoken(char **ps, char *es, char **q, char **eq);
t_cmd	*parseline(char **ps, char *es);
t_cmd	*parsecmd(char *s);
//parse2
int		s_scroll(char **s, char *es, int ret);
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
void	ffree(char *str);
void	mtxs_free(char **mtx);
char	*cmd_check(char **path, char *command);
void	execve_cmd(char **command, t_mini *mini);
void	ft_execute_command(char **command, t_mini *mini);
//runcmd/pathfinder
char	*path_ex(char *string, int ex_len, int start);
int		path_count(char *string, char c);
char	**ft_split(char *string, char c, int index, int start);
char	*ft_strnstr(const char *s, const char *to_find, size_t len);
char	**path_finder(char **envp);
//runcmd/runcmd
void	doc_cmd(t_cmd *cmd, char **envp);
void	runcmd(t_cmd *cmd, t_mini *mini);
//runcmd/runpipe
void	runpipe(t_pipecmd *pcmd, t_mini *mini);
//runcmd/runredir
int		eof_checker(char *line, char *rule);
void	here_doc(t_redircmd *rcmd, char *rule);
void	runredir(t_cmd *cmd, t_mini *mini);
//builtin
void	builtin_echo(char **args);
void	builtin_env(char **env);
void	builtin_exit(char **input);
//builtin/builtin_pwd
char	*true_pwd_ex();
void	builtin_pwd(char **envp);
//builtin/builtin_unset
void	remove_env_var(char **env, int i);
void	free_env_var(char *ex_env, char *ex_var);
void	unset_ccc(char *var, char **env);
void	builtin_unset(char **input, t_mini *mini);
//builtin/builtin_cd
char	*strjoin_path(char *path, int flag);
char	*path_builder(char *input, char *curr_pwd);
void	**pwd_mod(char *str, char **env);
void	**env_mod(char *path, char *curr_pwd, char **env);
void	**builtin_cd(char *input, char **env);
//builtin/export_is_valid
int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		arg_validation(char	*arg);
//builtin/export_print
void	p_export(char **env_cp);
void	sort_env(char **env);
//builtin/export_strjoins
char	*ft_strjoinf1(char *s1, char *s2);
char	*ft_strjoinf2(char *s1, char *s2);
char	*ft_strjoinf12(char *s1, char *s2);
//builtin/export_var_exp
char	*find_n_ret(char *name, char **env);
char	*ambient_value(char* str, char **env);
char	*exp_not_in_q(char *str, char *ret, char **env);
char	*quote_elab(char *str, int flag, char *ret, char **env);
char	*var_content_elab(char* var_c, char **env);
//builtin/export
char	what_is_next(char *str, int flag);
char	*a_var_update(char *var, char *env_l, char **env);
void	**export_ccc(char *var, char **env);
void	**ft_realloc(char **mtx, int size);
void	**builtin_export(char **input, char **env);
//utils/builtin_utils2
int		ft_strlen_g(const char *str);
int		builtin_exec(char **command, char **envp);
char	**env_cloner(char **envp);
//utils/builtin_utils
int		ft_count_words(char *s, char c);
void	strjoin_alloc(char **ps, char **mtx, int j, char c);
char	**ft_split_bt(char *s, char c);
void	exe_bt(char **input, t_mini *mini);
int		control_bt(char *input);

#endif
