NAME = ft_ssl

SRC = main.c mem.c

SRCS_DIR = ./srcs/

CFLAGS = #-Wall -Werror -Wextra

SRCS = $(addprefix $(SRCS_DIR), $(SRC))

OBJ = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
		gcc $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean
	make
