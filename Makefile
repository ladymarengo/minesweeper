all:
	g++ main.cpp cell.cpp sprite_sheet.cpp -w -lSDL2 -lSDL2_image -o minesweeper

run: all
	./minesweeper

clean:
	rm minesweeper