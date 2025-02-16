#include <ncurses/ncurses.h>
#include <string>
#include <chrono>
#include <thread>

void get_input(char &mv_input, std::string &mv_direction);
void move(int &Y_pos, int &X_pos, std::string mv_direction, int &mv_distance, const char *player_unit);

int main()
{
    int Y_pos = 1, X_pos = 1, mv_distance = 1, delay_ms = 150;
    std::string mv_direction = "east";
    char mv_input;
    const char *player_unit = "*";
    initscr();
    cbreak();
    curs_set(0);
    noecho();
    mvprintw(Y_pos, X_pos, "W to move up, A to move west, S to move south, D to move east, X to exit");
    getch();
    clear();
    refresh();
    nodelay(stdscr, true);
    while (true)
    {
        get_input(mv_input, mv_direction);
        move(Y_pos, X_pos, mv_direction, mv_distance, player_unit);
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
    }
    return 0;
}

void get_input(char &mv_input, std::string &mv_direction)
{
    mv_input = wgetch(stdscr);
    if (mv_input == 'w')
    {
        mv_direction = "north";
    }
    if (mv_input == 'a')
    {
        mv_direction = "west";
    }
    if (mv_input == 's')
    {
        mv_direction = "south";
    }
    if (mv_input == 'd')
    {
        mv_direction = "east";
    }
    if (mv_input == 'x')
    {
        exit(0);
    }
}

void move(int &Y_pos, int &X_pos, std::string mv_direction, int &mv_distance, const char *player_unit)
{
    if (mv_direction == "north")
    {
        mvaddch(Y_pos, X_pos, ' ');
        mvprintw(Y_pos -= mv_distance, X_pos, player_unit);
    }
    if (mv_direction == "west")
    {
        mvaddch(Y_pos, X_pos, ' ');
        mvprintw(Y_pos, X_pos -= (mv_distance * 2), player_unit);
    }
    if (mv_direction == "south")
    {
        mvaddch(Y_pos, X_pos, ' ');
        mvprintw(Y_pos += mv_distance, X_pos, player_unit);
    }
    if (mv_direction == "east")
    {
        mvaddch(Y_pos, X_pos, ' ');
        mvprintw(Y_pos, X_pos += (mv_distance * 2), player_unit);
    }
}