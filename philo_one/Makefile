NAME	= philo_one

HEADER	=	./philo_one.h

LIST	=	main.c	parser.c

OBJS	=	$(LIST:.c=.o)

GCC		= gcc -Wall -Wextra -Werror

all	: $(NAME)

$(NAME)	: $(HEADER) $(OBJS)
	$(GCC) $(OBJS) -o $(NAME) -pthread
#	@clear
	@echo Play?

clean	:
	rm -f $(OBJS)

fclean	: clean
	rm -f $(NAME)

re		: fclean all

.PHONY	: all clean fclean re bonus