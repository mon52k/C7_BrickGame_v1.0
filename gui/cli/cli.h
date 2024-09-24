#ifndef C_CLI_H_
#define C_CLI_H_

#include <curses.h>
#include "../../brick_game/tetris/tetris_lib.h"

void enable_ncurses(void);
void disable_ncurses(void);
void frontend_general_func(GameInfo_t game_info);

#endif
