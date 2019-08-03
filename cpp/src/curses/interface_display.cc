#include "interface.h"
#include "defines.h"
#include "game_settings.h"

#include <ncurses.h>

namespace reversi {
    inline void writeChar(char ch,const coordinate &c, coordinate &cursor) {
        if (c == cursor)
        {
            attron(A_BLINK | A_BOLD);
            mvaddch(c.y,2*c.x,ch);
            attroff(A_BLINK | A_BOLD);
        } else
        {
            mvaddch(c.y,2*c.x,ch);
        }
        
    }
}

void reversi::gui::updateWin(bool updateType) {
    typedef reversi::coordinate coordinate;
    // mutex for multi threading
    std::lock_guard<std::mutex> lockGuard(mutex);
    if (updateType) {
        for (int x = 0; x < BOARD_SIDE_LENGTH; x++)
        {
            for (int y = 0; y < BOARD_SIDE_LENGTH; y++)
            {
                coordinate c(x,y);
                switch (currBoard.getTile(c)->getPiece())
                {
                case empty:
                    attron(COLOR_PAIR(EMPTY_PAIR)| A_ALTCHARSET);
                    reversi::writeChar(ACS_BULLET,c,cursor);
                    attroff(COLOR_PAIR(EMPTY_PAIR)| A_ALTCHARSET);
                    break;
                case disabled:
                    attron(COLOR_PAIR(DISABLED_PAIR));
                    writeChar(DISABLED,c,cursor);
                    attroff(COLOR_PAIR(DISABLED_PAIR));
                    break;
                case white:
                    attron(COLOR_PAIR(WHITE_PAIR));
                    reversi::writeChar(WHITE,c,cursor);
                    attroff(COLOR_PAIR(WHITE_PAIR));
                    break;
                case black:
                    attron(COLOR_PAIR(BLACK_PAIR));
                    reversi::writeChar(BLACK,c,cursor);
                    attroff(COLOR_PAIR(BLACK_PAIR));
                    break;
                }
            }
        }
    }
    for (auto &&vm : validMoves)
    {
        attron(COLOR_PAIR(VALID_PAIR)| A_ALTCHARSET);
        writeChar(ACS_DIAMOND,*vm,cursor);
        attroff(COLOR_PAIR(VALID_PAIR));
    }
    if (suggested.x != -1)
    {
        attron(COLOR_PAIR(SUGGESTED_PAIR)|A_ALTCHARSET);
        reversi::writeChar(ACS_DIAMOND,suggested,cursor);
        attroff(COLOR_PAIR(SUGGESTED_PAIR)|A_ALTCHARSET);
    }
    switch (currBoard.getWho())
    {
    case white:
        mvaddch(BOARD_SIDE_LENGTH,0,WHITE);
        break;
    case black:
        mvaddch(BOARD_SIDE_LENGTH,0,BLACK);
        break;
    }
    mvaddstr(BOARD_SIDE_LENGTH,1,"'s Turn");
    wmove(stdscr,cursor.y,2*cursor.x);
    refresh();
}