#include "interface.h"
#include "defines.h"

#include <ncurses.h>

using namespace reversi;

gui::gui(): updateType(true){
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

    currBoard.getValidMoves(validMoves);
    cursor = *validMoves[0];
    // just assume this for now
    suggested = *validMoves[0];
    updateWin();
}

gui::~gui() {
    // think about removing the other thread
    clearList(validMoves);
    endwin();
}