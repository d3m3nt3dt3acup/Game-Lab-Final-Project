#include <ncurses/ncurses.h>
#include <chrono>
#include <thread>

void get_input(char &mv_input, char &mv_direction);
void move(int &Y_pos, int &X_pos, char mv_direction, int mv_distance, const char *player_unit);

int main()
{
    int Y_pos = 1, X_pos = 1;
    const int mv_distance = 1, delay_ms = 100;
    char mv_input, mv_direction = 'E';
    const char *player_unit = "*";
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    mvprintw(Y_pos, X_pos, "W to move up, A to move left, S to move down, D to move right, X to exit");
    refresh();
    getch();
    clear();
    nodelay(stdscr, true);
    while (true)
    {
        get_input(mv_input, mv_direction);
        move(Y_pos, X_pos, mv_direction, mv_distance, player_unit);
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
    }
    endwin();
    return 0;
}

void get_input(char &mv_input, char &mv_direction)
{
    mv_input = wgetch(stdscr);
    if (mv_input == 'w')
    {
        mv_direction = 'N';
    }
    if (mv_input == 'a')
    {
        mv_direction = 'W';
    }
    if (mv_input == 's')
    {
        mv_direction = 'S';
    }
    if (mv_input == 'd')
    {
        mv_direction = 'E';
    }
    if (mv_input == 'x')
    {
        exit(0);
    }
}

void move(int &Y_pos, int &X_pos, char mv_direction, int mv_distance, const char *player_unit)
{
    if (mv_direction == 'N')
    {
        mvaddch(Y_pos, X_pos, ' ');
        mvprintw(Y_pos -= mv_distance, X_pos, player_unit);
    }
    if (mv_direction == 'W')
    {
        mvaddch(Y_pos, X_pos, ' ');
        mvprintw(Y_pos, X_pos -= (mv_distance * 2), player_unit);
    }
    if (mv_direction == 'S')
    {
        mvaddch(Y_pos, X_pos, ' ');
        mvprintw(Y_pos += mv_distance, X_pos, player_unit);
    }
    if (mv_direction == 'E')
    {
        mvaddch(Y_pos, X_pos, ' ');
        mvprintw(Y_pos, X_pos += (mv_distance * 2), player_unit);
    }
}
