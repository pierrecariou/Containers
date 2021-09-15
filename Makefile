NAME            = ft_containers

STL				= stl

FT				= ft

HEADER          = ./

SRCS            = main.cpp

CFLAGS          = -std=c++98 -g -pedantic -Wall -Wextra -Werror

VARIABLE		= -DSTL=1

all:            $(NAME)

$(NAME):        $(SRCS)
				clang++ $(CFLAGS) -o $(NAME) $(SRCS)

clean:
				rm -f $(NAME) $(STL) $(FT)

fclean:
				rm -f $(NAME) $(STL) $(FT)

re:				fclean all

testexec:		$(SRCS)
				clang++ $(CFLAGS) $(VARIABLE) -o $(STL) $(SRCS)
				clang++ $(CFLAGS) -o $(FT) $(SRCS)

test:			testexec
				./test.sh

.PHONY:			all clean fclean test re
