NAME = minishell

SRC = main.c \
args/env_expander.c args/env_redirections.c args/take_args.c \
builtin/builtin_cd.c builtin/builtin_env.c builtin/builtin_exit.c builtin/builtin_export.c builtin/builtin_pwd.c builtin/builtin_unset.c \
execute/exec_functions.c execute/exec.c \
panic/panic_bt.c \
utils/builtin_utils.c utils/freeable.c utils/ft_atoi.c utils/ft_itoa.c utils/ft_split.c utils/ft_strjoin.c utils/ft_substr.c utils/utils_bt.c utils/utils_get_args.c utils/utils.c utils/utils2.c \

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
