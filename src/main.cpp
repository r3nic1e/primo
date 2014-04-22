#include <ncurses.h>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

fstream *openFile(char *filename)
{
	fstream *file = new fstream;
	file->open(filename);
	return file;
}

int printFile(fstream *file)
{
	char buffer[256];
	while (!file->eof())
	{
		file->getline(buffer, 256);
		addstr(buffer);
		int x, y;
		getyx(stdscr, y, x);
		move(0, y + 1);
		insdelln(1);
	}
	return 0;
}

int closeFile(fstream *file)
{
	file->close();
	delete file;
	return 0;
}

int main(int argc, char **argv)
{
	if (argc <= 1) return 0;
	char *filename = argv[1];
	fstream *file = openFile(filename);
	initscr();
	move(0, 0);
	printFile(file);
	refresh();
	getch();
	closeFile(file);
	endwin();
	return 0;
}
