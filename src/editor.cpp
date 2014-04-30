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
	status = newwin(1, xmax, ymax - 1, 0);
	keypad(win, true);
	scrollok(win, true);
	noecho();
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
	return 0;
}

int Editor::readFile()
{
	char str[256];
	while (!file->eof())
	{
		file->getline(str, 256);
		buf.addEnd(string(str));
	}
	return 0;
}

int Editor::closeFile()
{
	file->close();
	delete file;
	return 0;
}

int addToWindow(ListEntry<string> l, void* p)
{
	WINDOW *win = (WINDOW*) p;
	string str = l.data;
	waddstr(win, str.c_str());
	int y, x;
	getyx(win, y, x);
	wmove(win, y + 1, 0);
	return 0;
}

int Editor::view(unsigned y)
{
	wclear(win);
	wmove(win, 0, 0);
	buf.invoke(addToWindow, y, ywin, win);
	wrefresh(win);
	return 0;
}

void Editor::moveUp()
{
	int cy, cx;
	getyx(win, cy, cx);
	if (cy > 0) wmove(win, cy - 1, cx);
	else if (y > 0) view(--y);
//		copywin(pad, win, --y, x, 0, 0, ywin - 1, xwin - 1, false);
}

void Editor::moveDown()
{
	int cy, cx;
	getyx(win, cy, cx);
	if (cy < ywin - 1) wmove(win, cy + 1, cx);
	else if (y < lines - ywin) view(++y);
		//copywin(pad, win, ++y, x, 0, 0, ywin - 1, xwin - 1, false);
}

void Editor::moveLeft()
{
	int cy, cx;
	getyx(win, cy, cx);
	if (!cx)
	{
		moveUp();
		wmove(win, cy - 1, xwin - 1);
	}
	else if (buf.lines[y + cy]->data[cx] == '\t')
		wmove(win, cy, cx - 6);
	else if (buf.lines[y + cy]->data[cx] == '\0')
	{
		moveUp();
		wmove(win, cy - 1, cx);
	}
	else
		wmove(win, cy, cx - 1);
	wrefresh(win);
}

void Editor::moveRight()
{
	int cy, cx;
	getyx(win, cy, cx);
	if (buf.lines[y + cy]->data[cx] == '\t')
		wmove(win, cy, cx + 6);
	else if (buf.lines[y + cy]->data[cx] == '\0')
	{
		moveDown();
		wmove(win, cy + 1, 0);
	}
	else
		wmove(win, cy, cx + 1);
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
