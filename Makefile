
NAME 			= pipex

CC 				= cc

CFLAGS 			= -Wall -Wextra -Werror -I ./libft

DEPSFLAGS 		+= -MMD -MP

SRC_FILES		=	./srcs/ft_dup2.c \
					./srcs/ft_exec.c \
					./srcs/ft_find_path.c \
					./srcs/ft_first_child.c \
					./srcs/ft_middle_child.c \
					./srcs/ft_last_child.c \
					./srcs/ft_redirect_close_wait.c \
					./main.c

B_SRC_FILES		= 	./srcs/ft_dup2.c \
					./srcs/ft_exec.c \
					./srcs/ft_find_path.c \
					./srcs/ft_first_child.c \
					./srcs/ft_heredoc_bonus.c \
					./srcs/ft_middle_child.c \
					./srcs/ft_last_child.c \
					./srcs/ft_redirect_close_wait.c \
					./main_bonus.c


OBJECT_FILES = ${SRC_FILES:.c=.o}

B_OBJECT_FILES = ${B_SRC_FILES:.c=.o}

DEPS = ${SRC_FILES:.c=.d}

B_DEPS = ${B_SRC_FILES:.c=.d}

LIBFT = ./libft

all : mandatory

mandatory : .mandatory

.mandatory : ${OBJECT_FILES}
	${MAKE} -C ${LIBFT}
	${CC} -o ${NAME} ${CFLAGS} ${OBJECT_FILES} ${LIBFT}/libft.a
	@touch .mandatory
	@rm -f .bonus

bonus : .bonus

.bonus : ${B_OBJECT_FILES}
	${MAKE} -C ${LIBFT}
	${CC} -o ${NAME} ${CFLAGS} ${B_OBJECT_FILES} ${LIBFT}/libft.a
	@touch .bonus
	@rm -f .mandatory

%.o: %.c
	${CC} ${CFLAGS} ${DEPSFLAGS} -c -o $@ $<

-include ${DEPS}

clean :
	rm -f ${OBJECT_FILES} ${DEPS} ${B_OBJECT_FILES} ${B_DEPS}
	${MAKE} -C ${LIBFT} clean
	@rm -f .bonus .mandatory	

fclean :
	rm -f ${NAME} ${OBJECT_FILES} ${DEPS} ${B_OBJECT_FILES} ${B_DEPS}
	${MAKE} -C ${LIBFT} fclean
	@rm -f .bonus .mandatory

re : fclean all

redeps:
	touch ${DEPS}
	make
	${MAKE} -C ${LIBFT} redeps

.PHONY: all clean fclean re redeps libft