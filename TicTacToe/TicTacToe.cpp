#include <ncurses/ncurses.h>
#include <cstdlib>

void get_input(char &input, int &cursor_X, int &board_width, int &cursor_Y, int &board_height, char &char_on_cursor, WINDOW *board, char &current_player, char &previous_player, int &turn_counter, WINDOW *player, int &player_width);
void check_win(WINDOW *board, char &previous_player, WINDOW *title, int &title_width, char &another_game, WINDOW *player, int &player_width, WINDOW *instructions);
void win_routine(char &previous_player, WINDOW *title, int &title_width, char &another_game, WINDOW *board, WINDOW *player, int &player_width, WINDOW *instructions);
void check_draw(int &turn_counter, WINDOW *title, int &title_width, char &another_game, WINDOW *board, WINDOW *player, WINDOW *instructions, int &player_width);
void next_game(WINDOW *title, char &another_game, WINDOW *board, WINDOW *player, WINDOW *instructions);

int main()
{
    // initialize ncurses
    initscr();
    cbreak();
    noecho();

    // initialize variables
    char input, current_player = 'O', previous_player, char_on_cursor;
    int cursor_Y = 1, cursor_X = 3;
    int board_height = 7;
    int board_width = board_height * 3;
    int board_y = (LINES - board_height) / 2 - 1;
    int board_x = (COLS - board_width) / 2;
    int title_height = 3;
    int title_width = title_height * 7;
    int title_y = title_height;
    int title_x = (COLS - title_width) / 2;
    int player_height = 3;
    int player_width = player_height * 7;
    int player_y = player_height * 7 - 2;
    int player_x = (COLS - player_width) / 2;
    int instructions_height = 3;
    int instructions_width = instructions_height * 29;
    int instructions_y = instructions_height * 9 - 2;
    int instructions_x = (COLS - instructions_width) / 2;
    int turn_counter = 0;
    char another_game;

    // create windows
    WINDOW *board = newwin(board_height, board_width, board_y, board_x);
    WINDOW *title = newwin(title_height, title_width, title_y, title_x);
    WINDOW *player = newwin(player_height, player_width, player_y, player_x);
    WINDOW *instructions = newwin(instructions_height, instructions_width, instructions_y, instructions_x);

    // draw windows
    box(board, 0, 0);
    box(title, 0, 0);
    box(player, 0, 0);
    box(instructions, 0, 0);
    mvwhline(board, board_height / 3, 1, 0, board_width - 2);
    mvwhline(board, 2 * board_height / 3, 1, 0, board_width - 2);
    mvwvline(board, 1, board_width / 3, 0, board_height - 2);
    mvwvline(board, 1, 2 * board_width / 3, 0, board_height - 2);
    mvwprintw(title, 1, (title_width / 3) - 1, "TicTacToe");
    mvwprintw(player, 1, (player_width / 3) - 5, "Current player: O");
    mvwprintw(instructions, 1, 1, "A to move left, D to move right, W to move up, S to move down, Enter to place O or X");
    wrefresh(board);
    wrefresh(title);
    wrefresh(player);
    wrefresh(instructions);
    wmove(board, cursor_Y, cursor_X);
    curs_set(1);

    // main loop
    while (true)
    {
        get_input(input, cursor_X, board_width, cursor_Y, board_height, char_on_cursor, board, current_player, previous_player, turn_counter, player, player_width);
        check_win(board, previous_player, title, title_width, another_game, player, player_width, instructions);
        check_draw(turn_counter, title, title_width, another_game, board, player, instructions, player_width);
        wmove(board, cursor_Y, cursor_X);
    }

    return 0;
}

void get_input(char &input, int &cursor_X, int &board_width, int &cursor_Y, int &board_height, char &char_on_cursor, WINDOW *board, char &current_player, char &previous_player, int &turn_counter, WINDOW *player, int &player_width)
{
    // get input from board
    input = wgetch(board);

    // move the cursor
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

    // place O or X on the grid
    if (input == '\n')
    {
        char_on_cursor = winch(board);
        if (char_on_cursor == 'O' || char_on_cursor == 'X') {}
        else if (current_player == 'O')
        {
            wprintw(board, "O");
            mvwprintw(player, 1, (player_width / 3) - 5, "Current player: X");
            current_player = 'X';
            previous_player = 'O';
            turn_counter++;
        }
        else if (current_player == 'X')
        {
            wprintw(board, "X");
            mvwprintw(player, 1, (player_width / 3) - 5, "Current player: O");
            current_player = 'O';
            previous_player = 'X';
            turn_counter++;
        }
    }
    wrefresh(board);
    wrefresh(player);
}

void check_win(WINDOW *board, char &previous_player, WINDOW *title, int &title_width, char &another_game, WINDOW *player, int &player_width, WINDOW *instructions)
{
    // check for horizontal win
    if (mvwinch(board, 1, 3) == previous_player && mvwinch(board, 1, 10) == previous_player && mvwinch(board, 1, 17) == previous_player ||
        mvwinch(board, 3, 3) == previous_player && mvwinch(board, 3, 10) == previous_player && mvwinch(board, 3, 17) == previous_player ||
        mvwinch(board, 5, 3) == previous_player && mvwinch(board, 5, 10) == previous_player && mvwinch(board, 5, 17) == previous_player)
    {
        win_routine(previous_player, title, title_width, another_game, board, player, player_width, instructions);
    }

    // check for vertical win
    if (mvwinch(board, 1, 3) == previous_player && mvwinch(board, 3, 3) == previous_player && mvwinch(board, 5, 3) == previous_player ||
        mvwinch(board, 1, 10) == previous_player && mvwinch(board, 3, 10) == previous_player && mvwinch(board, 5, 10) == previous_player ||
        mvwinch(board, 1, 17) == previous_player && mvwinch(board, 3, 17) == previous_player && mvwinch(board, 5, 17) == previous_player)
    {
        win_routine(previous_player, title, title_width, another_game, board, player, player_width, instructions);
    }

    // check for diagonal win
    if (mvwinch(board, 1, 3) == previous_player && mvwinch(board, 3, 10) == previous_player && mvwinch(board, 5, 17) == previous_player)
    {
        win_routine(previous_player, title, title_width, another_game, board, player, player_width, instructions);
    }
    else if (mvwinch(board, 1, 17) == previous_player && mvwinch(board, 3, 10) == previous_player && mvwinch(board, 5, 3) == previous_player)
    {
        win_routine(previous_player, title, title_width, another_game, board, player, player_width, instructions);
    }
}

void win_routine(char &previous_player, WINDOW *title, int &title_width, char &another_game, WINDOW *board, WINDOW *player, int &player_width, WINDOW *instructions)
{
    // print winner in title
    curs_set(0);
    beep();
    if (previous_player == 'O')
    {
        mvwprintw(player, 1, (player_width / 3) - 5, "      O wins!    ");
    }
    else
    {
        mvwprintw(player, 1, (player_width / 3) - 5, "      X wins!    ");
    }
    wgetch(player);
    next_game(title, another_game, board, player, instructions);
}

void check_draw(int &turn_counter, WINDOW *title, int &title_width, char &another_game, WINDOW *board, WINDOW *player, WINDOW *instructions, int &player_width)
{
    // check for draw
    if (turn_counter == 9)
    {
        curs_set(0);
        beep();
        mvwprintw(player, 1, (player_width / 3) - 5, "       Draw!     ");
        wgetch(player);
        next_game(title, another_game, board, player, instructions);
    }
}

void next_game(WINDOW *title, char &another_game, WINDOW *board, WINDOW *player, WINDOW *instructions)
{
    // prompt user for confirmation
    mvwprintw(player, 1, 1, "Another game? (Y/N)");
    another_game = wgetch(player);
    while (another_game != 'Y' && another_game != 'y' && another_game != 'N' && another_game != 'n')
    {
        another_game = wgetch(player);
    }

    // start another game or exit
    if (another_game == 'Y' || another_game == 'y')
    {
        main();
    }
    else if (another_game == 'N' || another_game == 'n')
    {
        delwin(board);
        delwin(title);
        delwin(player);
        delwin(instructions);
        std::exit(EXIT_SUCCESS);
    }
}
