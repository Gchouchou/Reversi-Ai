#include "interface.h"
#include "defines.h"

#include <ncurses.h>

using namespace reversi;

gui::gui(): treeSearch(nullptr){
    // init screen
    initscr();
    keypad(stdscr, TRUE);
    cbreak();
    noecho();

    // check if there are colors
    if (has_colors() == FALSE) {
        endwin();
        printf("Your terminal does not support color\n");
        exit(1);
    }

    // initialize colors
    start_color();
    init_pair(EMPTY_PAIR,COLOR_MAGENTA,COLOR_BLACK);
    init_pair(WHITE_PAIR,COLOR_WHITE,COLOR_BLACK);
    init_pair(WHITE_PAIR,COLOR_WHITE,COLOR_BLACK);
    init_pair(VALID_PAIR,COLOR_YELLOW,COLOR_BLACK);
    init_pair(SUGGESTED_PAIR,COLOR_YELLOW,COLOR_GREEN);

    curs_set(1);
    suggested.x = -1;
    int ch = 0;
    while (ch != 'q')
    {
        updateWin();
        ch = getch();
        switch (ch)
        {
        case KEY_RIGHT:
            cursor.shift(right);
            break;
        case KEY_LEFT:
            cursor.shift(left);
            break;
        case KEY_UP:
            // oops bad design
            cursor.shift(down);
            break;
        case KEY_DOWN:
            // need to reverse this
            cursor.shift(up);
            break;
        case KEY_ENTER:
        case 10:
            currBoard.setDisabled(cursor);
            break;
        }
    }
    currBoard.clearDisabled();

    currBoard.getValidMoves(validMoves);
    cursor = *validMoves[0];
    // just assume this for now
    // suggested = *validMoves[0];
    updateWin();
}

gui::~gui() {
    // think about removing the other thread
    clearList(validMoves);
    delete(treeSearch);
    endwin();
}