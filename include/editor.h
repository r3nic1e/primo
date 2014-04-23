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
	std::fstream* file;
	WINDOW *pad, *win;
	int my, mx;
	int y, x;
};

#endif
