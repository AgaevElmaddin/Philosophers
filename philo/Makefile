NAME = philo

SRCS = philosopher.c subfunctions.c waiter.c end_program.c

OBJS = $(patsubst %.c, %.o, $(SRCS))

HEADER = philosopher.h

FLAGS = -Wall -Wextra -Werror

CC = gcc

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)
	# $(CC) $(FLAGS) $ˆ -o $@

%.o: %.c $(HEADER) Makefile
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
