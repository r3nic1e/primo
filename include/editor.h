#ifndef EDITOR_H
#define EDITOR_H

#include <fstream>
#include <ncurses.h>
#include <buffer.h>

enum mode {COMMAND, INSERT, REPLACE};

class Editor
{
public:
	Editor();
	int openFile(char *filename);
	int readFile();
	int closeFile();
	int view();
	int view(unsigned y);
	int commandLoop();
private:
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void setMode(mode m);

	Buffer buf;
	std::fstream* file;
	WINDOW *win;
	WINDOW *status;
	int ywin, xwin;
	int ymax, xmax;
	int y, x;
	int lines;
	mode currentMode;
};

#endif
