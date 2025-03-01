#include <ncurses/ncurses.h>

int main()
{
    initscr();
    cbreak();
    noecho();

    char input, current_player = 'O', char_on_cursor;
    int cursor_Y = 1, cursor_X = 3;
    int board_height = 7;
    int board_width = 21;
    int board_y = (LINES - board_height) / 2;
    int board_x = (COLS - board_width) / 2;
    int title_height = 3;
    int title_width = 21;
    int title_y = title_height;
    int title_x = (COLS - title_width) / 2;
    WINDOW *board = newwin(board_height, board_width, board_y, board_x);
    WINDOW *title = newwin(title_height, title_width, title_y, title_x);

    box(board, 0, 0);
    box(title, 0, 0);
    mvwhline(board, board_height / 3, 1, 0, board_width - 2);
    mvwhline(board, 2 * board_height / 3, 1, 0, board_width - 2);
    mvwvline(board, 1, board_width / 3, 0, board_height - 2);
    mvwvline(board, 1, 2* board_width / 3, 0, board_height - 2);
    mvwprintw(title, 1, title_width / 2, "tictactoe");
    wrefresh(board);
    wrefresh(title);
    wmove(board, cursor_Y, cursor_X);

    while((input = wgetch(board)) != 'q')
    {
        if (input == 'a')
        {
            if (cursor_X > 1)
            {
                cursor_X -= (board_width / 3);
            }
        }
        else if (input == 'd')
        {
            if (cursor_X < (board_width - 2))
            {
                cursor_X += (board_width / 3);
            }
        }
        else if (input == 'w')
        {
            if (cursor_Y > 1)
            {
                cursor_Y -= (board_height / 3);
            }
        }
        else if (input == 's')
        {
            if (cursor_Y < (board_height - 2))
            {
                cursor_Y += (board_height / 3);
            }
        }
        else if (input == '\n')
        {
            char_on_cursor = winch(board);
            if (char_on_cursor == 'O' || char_on_cursor == 'X')
            {
                continue;
            }
            else if (current_player == 'O')
            {
                wprintw(board, "O");
                current_player = 'X';
            }
            else if (current_player == 'X')
            {
                wprintw(board, "X");
                current_player = 'O';
            }
        }

        wmove(board, cursor_Y, cursor_X);
        wrefresh(board);
    }

    delwin(board);

    return 0;
}
