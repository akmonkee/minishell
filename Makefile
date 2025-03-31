NAME = minishell

SRC = main.c \
parser/parse.c parser/parse2.c parser/parsepipe.c parser/parseexec.c parser/nulterminate.c parser/parseredirs.c parser/parsequotes.c \
utils/utils.c utils/utils_2.c utils/freecmd.c utils/signal_utils.c utils/quote_utils.c utils/builtin_utils.c utils/builtin_utils2.c \
runcmd/runcmd.c runcmd/pathfinder.c runcmd/fullexecmd.c runcmd/runpipe.c runcmd/runredir.c \
builtin/builtin_cd.c builtin/builtin_env.c builtin/builtin_exit.c builtin/builtin_pwd.c builtin/builtin_echo.c builtin/builtin_unset.c \
builtin/builtin_export.c builtin/export_print.c builtin/export_is_valid.c builtin/export_strjoins.c builtin/export_var_exp.c \
builtin/export_av_n_ll.c \

OUT = $(SRC:.c=.o)

CC = gcc

FLAGS = -Wall -Werror -Wextra

READLINE = -lreadline -lncurses

%.c%.o:
		${CC} ${FLAGS} -g -c $< -o ${<:.c=.o}

$(NAME) : $(OUT)
		$(CC) $(FLAGS) $(OUT) -o $(NAME) $(READLINE)

all: $(NAME)

clean:
		rm -f $(OUT)

fclean: clean
	rm -f $(NAME)

re: fclean all
