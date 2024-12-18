/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:18:50 by msisto            #+#    #+#             */
/*   Updated: 2024/12/18 12:22:24 by msisto           ###   ########.fr       */
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
	t_cmd	*cmd;
	char		*file;
	char		*efile;
	int			mode;
	int			fd;
}	t_redircmd;

typedef struct s_pipecmd
{
	int			type;
	t_cmd	*left;
	t_cmd	*right;
}	t_pipecmd;

typedef struct s_listcmd
{
	int			type;
	t_cmd	*left;
	t_cmd	*right;
}	t_listcmd;

typedef struct s_backcmd
{
	int			type;
	t_cmd	*cmd;
}	t_back_cmd;

/*function delle t_da fare:
pipecmd
listcmd
backcmd
execcmd
redircmd
*/

/*function da fare:
parsecmd
	parseline
	parsepipe
	parseredir
	parseblock
	parseexec
nulterminate
getcmd
runcmd
panic (error function)*/

void	start_shell(char **envp);
//utils
int		ft_strchr(char *comp, char s);
size_t	ft_strlen(char	*s);
void	*ft_memset(void *b, int c, size_t len);
//parse
int			peek(char **ps, char *es, char *toks);
int			gettoken(char **ps, char *es, char **q, char **eq);
t_cmd	*parseline(char **ps, char *es);
t_cmd	*parsecmd(char *s);
//parse pipe
t_cmd	*parsepipe(char **ps, char *es);
//parseexec
t_cmd	*execcmd();
t_cmd	*parseexec(char **ps, char *es);
//parseredirs
t_cmd	*parseredirs(t_cmd *cmd, char **ps, char *es);
//nulterminate
t_cmd	*nulterminate(t_cmd *cmd);

#endif
