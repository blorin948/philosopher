$(VERBOSE).SILENT:

NAME =	philo_one

FLAGS = gcc -Wall -Werror -Wextra

HEADERS = philo_one.h

SRC =	fonctions.c\
		fork_think.c\
		init.c\
		loop.c\
		parse.c\
		philo_one.c

OBJ = $(patsubst %.c, obj/%.o, $(SRC))

all: $(NAME)

$(OBJ): ${HEADERS}

$(NAME): $(OBJ)
	@echo "\n==> Making philo one\n" 
	@$(FLAGS) $(OBJ) -o $(NAME)

obj/%.o: %.c
	@mkdir -p obj
	@$(FLAGS) -c $< -o $@

norme:
	norminette *.c *.h

clean:
	@echo "cleaning..."
	@rm -rf obj
	@echo done

fclean: clean
	@rm -rf $(NAME) obj
	@make -C ./libft fclean
	@make -C ./ft_printf fclean

re: fclean all

.PHONY:		all clean fclean re bonus run norme
