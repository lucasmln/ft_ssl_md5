NAME = ft_ssl

SRC = main.c mem.c ft_strdup.c sha256_algo.c ft_strncmp.c read_file.c

SRCS_DIR = ./srcs/

CFLAGS = #-Wall -Werror -Wextra

SRCS = $(addprefix $(SRCS_DIR), $(SRC))

OBJ = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
		clang $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean
	make
