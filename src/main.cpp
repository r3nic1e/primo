#include <ncurses.h>
#include <fstream>
#include <defines.h>
#include <editor.h>
#include <buffer.h>

using namespace std;

int main(int argc, char **argv)
{
	if (argc <= 1) return 0;
	char *filename = argv[1];
	initscr();
	Editor editor;
	editor.openFile(filename);
	editor.readFile();
	editor.closeFile();
	editor.view(0);
	editor.commandLoop();
	endwin();
	return 0;
}
