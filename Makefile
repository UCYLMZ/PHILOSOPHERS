SRCS = ./*.c \

NAME = philo
CC = gcc
CFLAGS =  -lpthread -g -fsanitize=thread
RM = rm -rf
LIBC = ar -rcs

all: ${NAME}

$(NAME): $(SRCS)
	@gcc $(SRCS) -o $(NAME)

clean:

fclean:
	@${RM} $(NAME)

re: fclean all

.PHONY: all clean fclean re