#----------------------------------------------------------------------------
#								VAR											
#----------------------------------------------------------------------------

NAME		= pipex
AR			= ar rcs #create library, (replace, create, sort)
RM			= rm -f
LIB			= ranlib
CC			= cc
CFLAGS 		= -Wall -Wextra -Werror

#----------------------------------------------------------------------------
#								DIRECTORY											
#----------------------------------------------------------------------------

HEAD			= ./includes/

#----------------------------------------------------------------------------
#								LIBFT											
#----------------------------------------------------------------------------

LIBFT			= ./libft/libft.a
LIBFT_DIR		=	./libft

SRC_FILES		= 	./srcs/ft_dup2.c \
					./srcs/ft_exec.c \
					./srcs/ft_find_path.c \
					./srcs/ft_first_child.c \
					./srcs/ft_last_child.c \
					./srcs/ft_redirect_close_wait.c \
					./main.c
OBJ_FILES		= $(SRC_FILES:.c=.o)
#----------------------------------------------------------------------------
#								TARGETS											
#----------------------------------------------------------------------------

%.o: %.c
	$(CC)  -c -I $(HEAD) $< -o $@


all: $(NAME)

$(NAME): $(OBJ_FILES)
	@make all -C $(LIBFT_DIR)
	@$(CC) $(OBJ_FILES) -L$(LIBFT_DIR) -lft -o $(NAME)  # Link with libft

clean:
	@make fclean -C $(LIBFT_DIR) 
	$(RM) $(OBJ_FILES)


fclean: clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
