#include <ncurses.h>
#include <fstream>

using namespace std;
WINDOW *pad, *win;
int my, mx;
int y, x;

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
		waddstr(pad, buffer);
		int x, y;
		getyx(pad, y, x);
		wmove(pad, y + 1, 0);
	}
	return 0;
}

int closeFile(fstream *file)
{
	file->close();
	delete file;
	return 0;
}

void commandLoop()
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
				if (y < 256) copywin(pad, win, ++y, x, 0, 0, my - 1, mx - 1, false);
				wrefresh(win);
				break;
			case 10:
				return;
			default:
				break;
		}
	}
}

int main(int argc, char **argv)
{
	if (argc <= 1) return 0;
	char *filename = argv[1];
	fstream *file = openFile(filename);
	initscr();
	win = newwin(0, 0, 0, 0);
	getmaxyx(win, my, mx);
	pad = newpad(256, mx);
	keypad(win, true);
	scrollok(win, true);
	noecho();
	wmove(pad, 0, 0);
	printFile(file);
	closeFile(file);
	x = 0;
	y = 1;
	copywin(pad, win, y, x, 0, 0, my - 1, mx - 1, false);
	wrefresh(win);
	commandLoop();
	endwin();
	return 0;
}
