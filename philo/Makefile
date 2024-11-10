CC = cc
# CFLAGS = -Wall -Wextra -Werror -g3 -O3
# CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g3 -O1
# CFLAGS = -fsanitize=thread -g3 -O1
CFLAGS = -g3 -O3

PHILO_NAME = philo

SRCS = ./srcs/
INCLUDE = ./includes/

PHILO_SRC = $(SRCS)philosopher.c \
			$(SRCS)main.c \
			$(SRCS)states.c \
			$(SRCS)init.c \
			$(SRCS)utils.c \
			$(SRCS)printer.c \
			$(SRCS)monitoring.c \
			$(SRCS)gettersetter.c \
			$(SRCS)fork_handler.c \
			$(SRCS)parsing.c


PHILO_OBJ = $(PHILO_SRC:.c=.o)

NAME = $(PHILO_NAME)
all: $(NAME)

$(PHILO_NAME): $(PHILO_OBJ)
	$(CC) $(CFLAGS) -I$(INCLUDE) -o $(PHILO_NAME) $(PHILO_OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

clean:
	rm -f $(PHILO_OBJ)

fclean: clean
	rm -f $(PHILO_NAME) $(NAME)

re: fclean all

push:
	git add .
	git commit -m "$(m)"
	git push

.PHONY: all clean fclean re
