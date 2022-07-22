NAME		:=	ft_ssl

CC			:=	clang
CFLAGS 		:=	-Wall -Werror -Wextra

SRCS_DIR	:=	srcs/
OBJ_DIR		:=	obj/

SRC			:=	main libft utils sha256_algo read_file printer \
				md5_algo parser sha224_algo sha512_algo sha384_algo

SRCS		:=	$(addprefix $(SRCS_DIR), $(addsuffix .c, $(SRC)))

OBJ 		:=	$(addprefix $(OBJ_DIR), $(SRCS:%.c=%.o))


all : $(NAME)

$(NAME) : $(OBJ)
		$(CC) -o $(NAME) $(CFLAGS) $(OBJ)

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)$(SRCS_DIR)

$(OBJ_DIR)%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(OBJ_DIR)

re: fclean
	make
