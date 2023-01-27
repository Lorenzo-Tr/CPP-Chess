NAME=Chess

CC=g++
FLAGS=-Wall
FLAGS+=-Werror
FLAGS+=-Wextra

DEBUG?=0
ifeq ($(DEBUG), 1)
  FLAGS+=-g3 -fsanitize=address
endif

VALGRIND_CHECK?=0
ifeq ($(VALGRIND_CHECK), 1)
  FLAGS+=-g
endif

OPTI?=0
ifeq ($(OPTI), 1)
  FLAGS+=-Ofast -ffast-math -march=native
endif

SRC_PATH=src/
SRC_NAME=main.cpp\
  ChessBoard.cpp\
  Piece.cpp\
  Player.cpp\
  Game.cpp

SRC=$(addprefix $(SRC_PATH), $(SRC_NAME))

INC_PATH=include/
INC_NAME=ChessBoard.hpp\
  Piece.hpp\
  Player.hpp\
  Game.hpp

INC=$(addprefix $(INC_PATH), $(INC_NAME))

OBJ_PATH=obj/
OBJ_NAME=$(addprefix $(OBJ_PATH), $(SRC_NAME))
OBJS=$(OBJ_NAME:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)
	
$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp
	@printf "Compiling $@"
	@printf "                     \\n\r"
	@$(CC) $(FLAGS) -I$(INC_PATH) -o $@ -c $<

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all