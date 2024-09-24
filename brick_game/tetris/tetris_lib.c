#include "tetris_lib.h"

#include "fsm.h"

void userInput(UserAction_t user_input, bool hold) {
  (void)hold;
  ExtendedGameInfo_t *game_info_ex = get_current_game_info_ex();
  if (!game_info_ex->new_input) {
    game_info_ex->input = user_input;
    game_info_ex->new_input = true;
  }
}

GameInfo_t updateCurrentState() {
  ExtendedGameInfo_t *game_info_ex = get_current_game_info_ex();
  finite_state_machine_func(game_info_ex);

  return game_info_ex->game_info;
}
