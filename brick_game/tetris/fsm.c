#include "fsm.h"

ExtendedGameInfo_t *get_current_game_info_ex() {
  static ExtendedGameInfo_t game_info_ex = {0};
  return &game_info_ex;
}

void finite_state_machine_func(ExtendedGameInfo_t *game_info_ex) {
  switch (game_info_ex->state) {
    case START:
      start_func(game_info_ex);
      break;
    case SPAWN:
      spawn_func(game_info_ex);
      break;
    case MOVING:
      moving_func(game_info_ex);
      break;
    case PAUSE:
      pause_func(game_info_ex);
      break;
    case SHIFTING:
      shifting_func(game_info_ex);
      break;
    case ATTACHING:
      attaching_func(game_info_ex);
      break;
    case GAMEOVER:
      game_over_func(game_info_ex);
      break;
    case EXIT_STATE:
      exit_func(game_info_ex);
      break;
    default:
      break;
  }
  prepare_game_field(game_info_ex);
}

void start_func(ExtendedGameInfo_t *game_info_ex) {
  if (game_info_ex->new_input) {
    switch (game_info_ex->input) {
      case Start:
        if (game_info_ex->game_info.pause == 2) {  // после game_over pause = 2
          restart_func(game_info_ex);
        }
        init_func(game_info_ex);
        generate_next_func(game_info_ex);
        game_info_ex->state = SPAWN;
        break;
      case Exit:
        game_info_ex->state = EXIT_STATE;
        break;
      default:
        break;
    }
  }
  game_info_ex->new_input = false;
}

void spawn_func(ExtendedGameInfo_t *game_info_ex) {
  next_to_tetromino(game_info_ex);
  generate_next_func(game_info_ex);
  brick_to_move_field(game_info_ex);
  game_info_ex->state = MOVING;
}

void moving_func(ExtendedGameInfo_t *game_info_ex) {
  if (game_info_ex->new_input) switch (game_info_ex->input) {
      case Rotate:
        action_func(game_info_ex);
      case Up:
        break;
      case Down:
        game_info_ex->state = SHIFTING;
        break;
      case Right:
        move_brick_right(game_info_ex);
        break;
      case Left:
        move_brick_left(game_info_ex);
        break;
      case Exit:
        game_info_ex->state = EXIT_STATE;
        break;
      case Pause:
        game_info_ex->state = PAUSE;
        game_info_ex->game_info.pause = 1;
        break;
      default:
        break;
    }
  if (check_move_to_shift_func(game_info_ex)) {
    game_info_ex->state = SHIFTING;
  }
  game_info_ex->new_input = false;
}

void pause_func(ExtendedGameInfo_t *game_info_ex) {
  if (game_info_ex->new_input) {
    switch (game_info_ex->input) {
      case Pause:
        game_info_ex->game_info.pause = 0;
        game_info_ex->state = MOVING;
        break;
      case Exit:
        game_info_ex->state = EXIT_STATE;
        break;
      default:
        break;
    }
  }
  game_info_ex->new_input = false;
}

void shifting_func(ExtendedGameInfo_t *game_info_ex) {
  if (check_shifting_to_attaching(game_info_ex)) {
    game_info_ex->state = ATTACHING;
  } else {
    move_brick(game_info_ex);
    game_info_ex->state = MOVING;
  }
}

void attaching_func(ExtendedGameInfo_t *game_info_ex) {
  move_from_move_to_touch(game_info_ex);
  count_game_score(game_info_ex);
  if (check_game_over(game_info_ex))
    game_info_ex->state = GAMEOVER;
  else
    game_info_ex->state = SPAWN;
}

void game_over_func(ExtendedGameInfo_t *game_info_ex) {
  game_info_ex->state = START;
  game_info_ex->game_info.pause = 2;
}

void exit_func(ExtendedGameInfo_t *game_info_ex) {
  dealloc_field(&(game_info_ex->game_info.field), ROWS_MAP);
  dealloc_field(&(game_info_ex->game_info.next), NEXT_SIZE);
  game_info_ex->game_info.pause = 3;
}
