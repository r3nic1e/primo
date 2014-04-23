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
	lines = 56;
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

void Editor::scrollUp(int cy, int cx)
{
	if (cy > 0) wmove(win, cy - 1, cx);
	else if (y > 0) copywin(pad, win, --y, x, 0, 0, my - 1, mx - 1, false);
	wrefresh(win);
}

void Editor::scrollDown(int cy, int cx)
{
	if (cy < my - 1) wmove(win, cy + 1, cx);
	else if (y < lines - 1) copywin(pad, win, ++y, x, 0, 0, my - 1, mx - 1, false);
	wrefresh(win);
}

void Editor::scrollLeft(int cy, int cx)
{
	if (cx > 0) wmove(win, cy, cx - 1);
	else
	{
		scrollUp(cy, cx);
		wmove(win, cy - 1, mx - 1);
	}	
	wrefresh(win);
}

void Editor::scrollRight(int cy, int cx)
{
	if (cx < mx - 1) wmove(win, cy, cx + 1);
	else
	{
		scrollDown(cy, cx);
		wmove(win, cy + 1, 0);
	}
	wrefresh(win);
}

int Editor::commandLoop()
{
	while (true)
	{
		int c = wgetch(win);
		int cy, cx;
		getyx(win, cy, cx);
		switch (c)
		{
			case KEY_UP:
				scrollUp(cy, cx);
				break;
			case KEY_DOWN:
				scrollDown(cy, cx);
				break;
			case KEY_LEFT:
				scrollLeft(cy, cx);
				break;
			case KEY_RIGHT:
				scrollRight(cy, cx);
				break;
			case 10:
				return 0;
			default:
				break;
		}
	}
	return 0;
}
