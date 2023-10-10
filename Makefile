CXX		=	g++

CXXFLAGS	+=	-Wall -pedantic -std=c++17 -fPIC

LDFLAGS		=	-ldl

## arcade

NAME		=	arcade

SRC_DIR		=	core/

SRC		=	main.cpp			\
			$(SRC_DIR)CoreDrawer.cpp		\
			$(SRC_DIR)Core.cpp		\
			$(SRC_DIR)Libhandler.cpp	\


OBJ		=	$(SRC:.cpp=.o)

NAME_SFML	=	lib/arcade_sfml.so

SRC_SFML	=	graphs/LibSFML.cpp

OBJ_SFML	=	$(SRC_SFML:.cpp=.o)

LDFLAGS_SFML	=	-shared -fPIC -lsfml-graphics -lsfml-system -lsfml-window -lsfml-audio

## plugin SDL

NAME_SDL	=	lib/arcade_sdl2.so

SRC_SDL	=	graphs/LibSDL.cpp	\

OBJ_SDL	=	$(SRC_SDL:.cpp=.o)

LDFLAGS_SDL	=	-shared -fPIC `sdl2-config --cflags --libs` -lSDL2_ttf -lSDL2_image -lSDL2_mixer

## plugin GL

NAME_RL	=	lib/arcade_rayLib.so

SRC_RL	=	graphs/LibrayLib.cpp	\

OBJ_RL	=	$(SRC_RL:.cpp=.o)

LDFLAGS_RL	=	-shared -fPIC -l raylib -lGL -lm -lpthread -ldl -lrt -lX11

## plugin ncurses

NAME_NCURSES	=	lib/arcade_ncurses.so

SRC_NCURSES	=	graphs/LibNCURSES.cpp

OBJ_NCURSES	=	$(SRC_NCURSES:.cpp=.o)

LDFLAGS_NCURSES	=	-shared -fPIC -lncurses

## pacman

NAME_PACMAN	=	lib/arcade_pacman.so

SRC_PACMAN	=	games/pacman.cpp   \

OBJ_PACMAN	=	$(SRC_PACMAN:.cpp=.o)

LDFLAGS_PACMAN	=	-shared -fPIC

## snake

NAME_SNAKE	=	lib/arcade_snake.so

SRC_SNAKE	=	games/snake.cpp

OBJ_SNAKE	=	$(SRC_SNAKE:.cpp=.o)

LDFLAGS_SNAKE	=	-shared -fPIC

all:			core games graphicals

create_dir:
			mkdir -p lib

core:			$(NAME)

games:			create_dir $(NAME_PACMAN)  $(NAME_SNAKE)

graphicals:		create_dir $(NAME_RL) $(NAME_SFML) $(NAME_NCURSES) $(NAME_SDL)

$(NAME_SFML):		$(OBJ_SFML)
			$(CXX) $(OBJ_SFML) -o $(NAME_SFML) $(LDFLAGS_SFML)

$(NAME_SDL):		$(OBJ_SDL)
			$(CXX) $(OBJ_SDL) -o $(NAME_SDL) $(LDFLAGS_SDL)

$(NAME_NCURSES):		$(OBJ_NCURSES)
			$(CXX) $(OBJ_NCURSES) -o $(NAME_NCURSES) $(LDFLAGS_NCURSES)

$(NAME_RL):		$(OBJ_RL)
			$(CXX) $(OBJ_RL) -o $(NAME_RL) $(LDFLAGS_RL)

$(NAME_PACMAN):		$(OBJ_PACMAN)
			$(CXX) $(OBJ_PACMAN) -o $(NAME_PACMAN) $(LDFLAGS_PACMAN)

$(NAME_SNAKE):		$(OBJ_SNAKE)
			$(CXX) $(OBJ_SNAKE) -o $(NAME_SNAKE) $(LDFLAGS_SNAKE)

$(NAME):		$(OBJ)
			$(CXX) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
			rm -rf lib
			$(RM) $(OBJ_SFML) $(OBJ_PACMAN) $(OBJ_NCURSES) $(OBJ_SNAKE) $(OBJ_SDL) $(OBJ_RL) $(OBJ)

fclean:			clean
			$(RM) $(NAME_SFML) $(NAME_PACMAN) $(NAME_SDL) $(NAME_RL) $(NAME_NCURSES) $(NAME_SNAKE) $(NAME)

re:			fclean all

.PHONY:			clean fclean re all