#ifndef EDITOR_H
#define EDITOR_H

#include <fstream>
#include <ncurses.h>

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
	void scrollUp(int cy, int cx);
	void scrollDown(int cy, int cx);
	void scrollLeft(int cy, int cx);
	void scrollRight(int cy, int cx);
	std::fstream* file;
	WINDOW *pad, *win;
	int my, mx;
	int y, x;
	int lines;
};

#endif
