#ifndef FSM_H
#define FSM_H

#include "tetris_logic.h"

ExtendedGameInfo_t *get_current_game_info_ex();
void finite_state_machine_func(ExtendedGameInfo_t *game_info_ex);

void start_func(ExtendedGameInfo_t *game_info_ex);
void spawn_func(ExtendedGameInfo_t *game_info_ex);
void moving_func(ExtendedGameInfo_t *game_info_ex);
void pause_func(ExtendedGameInfo_t *game_info_ex);
void shifting_func(ExtendedGameInfo_t *game_info_ex);
void attaching_func(ExtendedGameInfo_t *game_info_ex);
void game_over_func(ExtendedGameInfo_t *game_info_ex);
void exit_func(ExtendedGameInfo_t *game_info_ex);

#endif
