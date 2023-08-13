SRCS = 		./philosophers.c ./routine.c ./utils_control.c \
		 	./utils_lock_time.c utils_numbers.c utils_philosophers.c

OBJS = $(SRCS:.c=.o)

NAME = philosophers
CC = gcc
CFLAGS =  -g -fsanitize=thread -Wall -Wextra -Werror
RM = rm -rf

all: ${NAME}

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "\x1b[42mPhilosophers is creating!"

%.o: %.c
	@$(CC) $(C_FLAGS) -c $< -o $@

clean:
	@${RM} ${OBJS}
	@echo "\x1b[38;5;3mObjects are deleting!"

fclean:
	@${RM} $(NAME)
	@${RM} ${OBJS}
	@echo "\x1b[38;5;3mAll files are deleting!"

re: fclean all

.PHONY: all clean fclean re