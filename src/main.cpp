#include <ncurses.h>
#include <fstream>
#include <defines.h>
#include <editor.h>
#include <buffer.h>

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


int main(int argc, char **argv)
{
	if (argc <= 1) return 0;
	char *filename = argv[1];
	initscr();
	Editor editor;
	editor.openFile(filename);
	editor.printFile();
	editor.closeFile();
	editor.view();
	editor.commandLoop();
	endwin();
	return 0;
}
