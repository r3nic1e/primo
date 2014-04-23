#include <editor.h>
#include <defines.h>
#include <fstream>
#include <ncurses.h>

using namespace std;

Editor::Editor()
{
	win = newwin(0, 0, 0, 0);
	getmaxyx(win, my, mx);
	pad = newpad(PADSIZE, mx);
	keypad(win, true);
	scrollok(win, true);
	noecho();
	wmove(pad, 0, 0);
	wmove(win, 0, 0);
	y = x = 0;
}

int Editor::openFile(char *filename)
{
	file = new fstream();
	file->open(filename);
	return 0;
}

int Editor::printFile()
{
	char buffer[256];
	while (!file->eof())
	{
		file->getline(buffer, 256);
		waddstr(pad, buffer);
		int x, y;
		getyx(pad, y, x);
		wmove(pad, y + 1, 0);
	}
	return 0;
}

int Editor::closeFile()
{
	file->close();
	delete file;
	return 0;
}

int Editor::view()
{
	copywin(pad, win, y, x, 0, 0, my - 1, mx - 1, false);
	wrefresh(win);
	return 0;
}

int Editor::commandLoop()
{
	while (true)
	{
		int c = wgetch(win);
		switch (c)
		{
			case KEY_UP:
				if (y > 0) copywin(pad, win, --y, x, 0, 0, my - 1, mx - 1, false);
				wrefresh(win);
				break;
			case KEY_DOWN:
				if (y < PADSIZE - 1) copywin(pad, win, ++y, x, 0, 0, my - 1, mx - 1, false);
				wrefresh(win);
				break;
			case 10:
				return 0;
			default:
				break;
		}
	}
	return 0;
}
