NAME = minesweeper
INCL = -Iincludes/
FILES = main cell cells sprite_sheet
SRCS = $(patsubst %, srcs/%.cpp, $(FILES))

all:
	g++ $(SRCS) -lSDL2 -lSDL2_image $(INCL) -o $(NAME)

re: clean all

run: all
	./$(NAME)

clean:
	rm $(NAME)