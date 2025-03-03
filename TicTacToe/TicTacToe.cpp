#include <ncurses/ncurses.h>

int main()
{
    initscr();
    cbreak();
    noecho();

    char input, current_player = 'O', previous_player, char_on_cursor;
    int cursor_Y = 1, cursor_X = 3;
    int board_height = 7;
    int board_width = board_height * 3;
    int board_y = (LINES - board_height) / 2;
    int board_x = (COLS - board_width) / 2;
    int title_height = 3;
    int title_width = 21;
    int title_y = title_height;
    int title_x = (COLS - title_width) / 2;
    int turn_counter = 0;
    char another_game;
    WINDOW *board = newwin(board_height, board_width, board_y, board_x);
    WINDOW *title = newwin(title_height, title_width, title_y, title_x);

    box(board, 0, 0);
    box(title, 0, 0);
    mvwhline(board, board_height / 3, 1, 0, board_width - 2);
    mvwhline(board, 2 * board_height / 3, 1, 0, board_width - 2);
    mvwvline(board, 1, board_width / 3, 0, board_height - 2);
    mvwvline(board, 1, 2 * board_width / 3, 0, board_height - 2);
    mvwprintw(title, 1, (title_width / 3) - 1, "TicTacToe");
    wrefresh(board);
    wrefresh(title);
    wmove(board, cursor_Y, cursor_X);

    while ((input = wgetch(board)) != 'q')
    {
        if (input == 'a')
        {
            if (cursor_X > 3)
            {
                cursor_X -= (board_width / 3);
            }
        }
        else if (input == 'd')
        {
            if (cursor_X < (board_width - 4))
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
                previous_player = 'O';
                turn_counter++;
            }
            else if (current_player == 'X')
            {
                wprintw(board, "X");
                current_player = 'O';
                previous_player = 'X';
                turn_counter++;
            }
        }
        wrefresh(board);

        // check win in horizontal
        if (mvwinch(board, 1, 3) == previous_player && mvwinch(board, 1, 10) == previous_player && mvwinch(board, 1, 17) == previous_player ||
            mvwinch(board, 3, 3) == previous_player && mvwinch(board, 3, 10) == previous_player && mvwinch(board, 3, 17) == previous_player ||
            mvwinch(board, 5, 3) == previous_player && mvwinch(board, 5, 10) == previous_player && mvwinch(board, 5, 17) == previous_player)
        {
            curs_set(0);
            beep();
            mvwprintw(title, 1, (title_width / 3) - 1, "  Winner!");
            wgetch(title);
            break;
        }
        // check win in vertical
        if (mvwinch(board, 1, 3) == previous_player && mvwinch(board, 3, 3) == previous_player && mvwinch(board, 5, 3) == previous_player ||
            mvwinch(board, 1, 10) == previous_player && mvwinch(board, 3, 10) == previous_player && mvwinch(board, 5, 10) == previous_player ||
            mvwinch(board, 1, 17) == previous_player && mvwinch(board, 3, 17) == previous_player && mvwinch(board, 5, 17) == previous_player)
        {
            curs_set(0);
            beep();
            mvwprintw(title, 1, (title_width / 3) - 1, "  Winner!");
            wgetch(title);
            break;
        }
        // check win in backslash diagonal
        if (mvwinch(board, 1, 3) == previous_player && mvwinch(board, 3, 10) == previous_player && mvwinch(board, 5, 17) == previous_player)
        {
            curs_set(0);
            beep();
            mvwprintw(title, 1, (title_width / 3) - 1, "  Winner!");
            wgetch(title);
            break;
        }
        // check win in forward slash diagonal
        if (mvwinch(board, 1, 17) == previous_player && mvwinch(board, 3, 10) == previous_player && mvwinch(board, 5, 3) == previous_player)
        {
            curs_set(0);
            beep();
            mvwprintw(title, 1, (title_width / 3) - 1, "  Winner!");
            wgetch(title);
            break;
        }
        // check draw
        if (turn_counter == 9)
        {
            curs_set(0);
            beep();
            mvwprintw(title, 1, (title_width / 3) - 1, "  Draw!  ");
            wgetch(title);
            break;
        }

        wmove(board, cursor_Y, cursor_X);
    }

    mvwprintw(title, 1, 1, "Another game? (Y/N)");
    another_game = wgetch(title);
    while (another_game != 'Y' && another_game != 'y' && another_game != 'N' && another_game != 'n')
    {
        another_game = wgetch(title);
    }

    if (another_game == 'Y' || another_game == 'y')
    {
        curs_set(1);
        main();
    }
    else if (another_game == 'N' || another_game == 'n')
    {
        delwin(board);
        delwin(title);
        return 0;
    }

    return 0;
}
