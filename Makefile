NAME = minishell

SRC = main.c \
execute/exec_functions.c execute/exec.c \
utils/utils.c utils/utils_bt.c utils/ft_strjoin.c utils/get_arg.c \
builtin/builtin_pwd.c builtin/builtin_utils.c \

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
