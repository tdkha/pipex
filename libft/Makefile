#----------------------------------------------------------------------------
#								VAR											
#----------------------------------------------------------------------------

NAME		= libft.a
AR			= ar rcs #create library, (replace, create, sort)
RM			= rm -f
LIB			= ranlib
CC			= cc
CFLAGS 		= -Wall -Wextra -Werror

#----------------------------------------------------------------------------
#								DIRECTORY											
#----------------------------------------------------------------------------

HEAD			= ./includes/
SRC_FILES		= 	./ft_atoi.c ./ft_bzero.c ./ft_calloc.c \
					./ft_isalnum.c ./ft_isalpha.c ./ft_isascii.c ./ft_isdigit.c ./ft_isprint.c \
					./ft_itoa.c \
					./ft_memchr.c ./ft_memcmp.c ./ft_memcpy.c ./ft_memmove.c ./ft_memset.c \
					./ft_putchar_fd.c ./ft_putendl_fd.c ./ft_putnbr_fd.c ./ft_putstr_fd.c \
					./ft_split.c ./ft_strchr.c ./ft_strdup.c ./ft_striteri.c ./ft_strjoin.c ./ft_strlcat.c \
					./ft_strlcpy.c ./ft_strlen.c ./ft_strmapi.c ./ft_strncmp.c ./ft_strnstr.c ./ft_strrchr.c \
					./ft_strtrim.c ./ft_substr.c ./ft_split.c \
					./ft_tolower.c ./ft_toupper.c 
SRC_BONUS_FILES	=	./ft_lstnew_bonus.c ./ft_lstadd_front_bonus.c ./ft_lstsize_bonus.c ./ft_lstlast_bonus.c ./ft_lstadd_back_bonus.c \
					./ft_lstdelone_bonus.c ./ft_lstclear_bonus.c ./ft_lstiter_bonus.c ./ft_lstmap_bonus.c
OBJ_FILES		= $(SRC_FILES:.c=.o)
OBJ_BONUS_FILES = $(SRC_BONUS_FILES:.c=.o)
#----------------------------------------------------------------------------
#								TARGETS											
#----------------------------------------------------------------------------


all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(AR) $(NAME) $(OBJ_FILES)
	$(LIB) $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c -I $(HEAD) $< -o $@

bonus: .bonus

.bonus: $(NAME) $(OBJ_BONUS_FILES) 
	$(AR) $(NAME) $(OBJ_BONUS_FILES)
	$(LIB) $(NAME)
	@touch .bonus

clean:
	$(RM) $(OBJ_FILES) $(OBJ_BONUS_FILES)
	@rm -f .bonus

fclean: clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re bonus