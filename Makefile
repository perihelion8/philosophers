.PHONY: all clean fclean re

NAME	:= philo
CC		:= cc
CFLAGS	:= -Wall -Werror -Wextra -pthread
SRC		:= main.c rules.c monitor.c time.c philo.c philo_routine.c philo_print.c
OBJ		:= $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
