#include <editor.h>
#include <buffer.h>
#include <defines.h>
#include <fstream>
#include <ncurses.h>

using namespace std;

Editor::Editor()
{
	getmaxyx(stdscr, ymax, xmax);
	win = newwin(ymax - 2, xmax, 0, 0);
	getmaxyx(win, ywin, xwin);
	pad = newpad(PADSIZE, xwin);
	status = newwin(1, xmax, ymax - 1, 0);
	keypad(win, true);
	scrollok(win, true);
	noecho();
	wmove(pad, 0, 0);
	wmove(win, 0, 0);
	y = x = 0;
	setMode(COMMAND);
}

void Editor::setMode(mode m)
{
	currentMode = m;
	wclear(status);
	switch (m)
	{
		case COMMAND:
			wprintw(status, "Command");
			break;
		case INSERT:
			wprintw(status, "Insert");
			break;
		case REPLACE:
			wprintw(status, "Replace");
			break;
	}
	wrefresh(status);
}

int Editor::openFile(char *filename)
{
	file = new fstream();
	file->open(filename);
	lines = 0;
	while (!file->eof())
		if (file->get() == '\n') lines++;
	file->close();
	file->open(filename);
	return 0;
}

int addToWindow(ListEntry<char*> l, void* p)
{
	WINDOW *pad = (WINDOW*) p;
	char* str = l.data;
	waddstr(pad, str);
	int y, x;
	getyx(pad, y, x);
	wmove(pad, y + 1, 0);
	return 0;
}

int Editor::printFile()
{
	char str[256];
	while (!file->eof())
	{
		file->getline(str, 256);
		buf.addEnd(str);
/*		waddstr(pad, buf);
		int x, y;
		getyx(pad, y, x);
		wmove(pad, y + 1, 0);
*/	}
	buf.invoke(addToWindow, pad);
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
	copywin(pad, win, y, x, 0, 0, ywin - 1, xwin - 1, false);
	wrefresh(win);
	return 0;
}

void Editor::moveUp()
{
	int cy, cx;
	getyx(win, cy, cx);
	if (cy > 0) wmove(win, cy - 1, cx);
	else if (y > 0) copywin(pad, win, --y, x, 0, 0, ywin - 1, xwin - 1, false);
	wrefresh(win);
}

void Editor::moveDown()
{
	int cy, cx;
	getyx(win, cy, cx);
	if (cy < ywin - 1) wmove(win, cy + 1, cx);
	else if (y < lines - ywin) copywin(pad, win, ++y, x, 0, 0, ywin - 1, xwin - 1, false);
	wrefresh(win);
}

void Editor::moveLeft()
{
	int cy, cx;
	getyx(win, cy, cx);
	if (cx > 0) wmove(win, cy, cx - 1);
	else
	{
		moveUp();
		wmove(win, cy - 1, xwin - 1);
	}	
	wrefresh(win);
}

void Editor::moveRight()
{
	int cy, cx;
	getyx(win, cy, cx);
	if (cx < xwin - 1)
	{
		if (winch(win) == ' ') wmove(win, cy, cx + 2);
		else wmove(win, cy, cx + 1);
	}
	else
	{
		moveDown();
		wmove(win, cy + 1, 0);
	}
	wrefresh(win);
}

int Editor::commandLoop()
{
	while (true)
	{
		int c = wgetch(win);
		switch (c)
		{
			case KEY_UP:
				moveUp();
				break;
			case KEY_DOWN:
				moveDown();
				break;
			case KEY_LEFT:
				moveLeft();
				break;
			case KEY_RIGHT:
				moveRight();
				break;
			case 'i':
				setMode(INSERT);
				break;
			case 'r':
				setMode(REPLACE);
				break;
			case 27:
				setMode(COMMAND);
				break;
			case 'q':
				return 0;
			default:
				break;
		}
	}
	return 0;
}
