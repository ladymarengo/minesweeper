all:
	g++ main.cpp cells.cpp sprite_sheet.cpp -w -lSDL2 -lSDL2_image -o minesweeper

clean:
	rm minesweeper