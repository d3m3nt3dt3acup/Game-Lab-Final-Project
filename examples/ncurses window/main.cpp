#include <ncurses/ncurses.h>

int main()
{
    initscr();
    cbreak();
    noecho();
    curs_set(0);

    int win_height = 10;
    int win_width = 30;
    int win_y = (LINES - win_height) / 2;
    int win_x = (COLS - win_width) / 2;
    WINDOW *my_window = newwin(win_height, win_width, win_y, win_x);

    box(my_window, 0, 0);
    mvwprintw(my_window, 1, 1, "Hello, world!");
    wrefresh(my_window);
    wgetch(my_window);
    delwin(my_window);

    return 0;
}
