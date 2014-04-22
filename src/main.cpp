#include <ncurses.h>

int main(int argc, char **argv)
{
	initscr();
	move(10, 25);
	printw("Hi world!\n");
	refresh();
	getch();
	endwin();
	return 0;
}
