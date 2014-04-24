#ifndef EDITOR_H
#define EDITOR_H

#include <fstream>
#include <ncurses.h>

enum mode {COMMAND, INSERT, REPLACE};

class Editor
{
public:
	Editor();
	int openFile(char *filename);
	int printFile();
	int closeFile();
	int view();
	int commandLoop();
private:
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void setMode(mode m);

	std::fstream* file;
	WINDOW *pad, *win;
	WINDOW *status;
	int ywin, xwin;
	int ymax, xmax;
	int y, x;
	int lines;
	mode currentMode;
};

#endif
