NAME = philo_bonus

SRCS = philo_bonus.c subfunctions_bonus.c waiter_bonus.c end_program_bonus.c

OBJS = $(patsubst %.c, %.o, $(SRCS))

HEADER = philo_bonus.h

FLAGS = -Wall -Wextra -Werror

CC = gcc

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HEADER) Makefile
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
