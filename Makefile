NAME            = ft_containers

HEADER          = ./

SRCS            = main.cpp

CFLAGS          = -std=c++98 -g -pedantic -Wall -Wextra -Werror

all:            $(NAME)

$(NAME):        $(SRCS)
				clang++ $(CFLAGS) -o $(NAME) $(SRCS)

clean:
				rm -f $(NAME)

fclean:
				rm -f $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
