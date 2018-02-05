// show ncurses code for pressed key

#include <stdio.h>
#include <ncurses.h>

int main()
{
    int c;
    initscr();
    curs_set(0);
    noecho();
    cbreak();

    mvprintw(24, 0, "Type any key. ESC exits.");

    refresh();

    // ESC has code 27
    while((c = getch()) != 27) {
        mvprintw(24, 0, "Character pressed is = %3d. Hopefully it can be printed as '%c'", c, c);
        refresh();
    }

    clrtoeol();
    refresh();
    endwin();
    return 0;
}
