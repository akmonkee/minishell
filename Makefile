NAME = minishell

SRC = main.c parser/parse.c parser/parsepipe.c parser/parseexec.c parser/nulterminate.c parser/parseredirs.c utils/utils.c

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
