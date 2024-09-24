#include "tetris_logic.h"

void brick_to_move_field(ExtendedGameInfo_t *game_info_ex) {
  int x = game_info_ex->tetromino.x;
  int y = game_info_ex->tetromino.y;
  reset_static_field(game_info_ex->move_field);
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      if (game_info_ex->tetromino.brick[i][j] == 1)
        game_info_ex->move_field[i + x][j + y] = 1;
}

void action_func(ExtendedGameInfo_t *game_info_ex) {
  Tetromino tmp_tetr = {0};
  copy_tetr(&tmp_tetr, &(game_info_ex->tetromino));

  if (game_info_ex->tetromino.current_type == 'i') {
    turn_stick_func(&(game_info_ex->tetromino));
  } else if (game_info_ex->tetromino.current_type != 'o') {
    turn_other_func(&(game_info_ex->tetromino));
  }

  if (check_x_after_action(game_info_ex)) {
    copy_tetr(&(game_info_ex->tetromino), &tmp_tetr);
  }
  check_y_after_action(game_info_ex);
  brick_to_move_field(game_info_ex);
  if (check_tetr_collision_after_action(game_info_ex)) {
    copy_tetr(&(game_info_ex->tetromino), &tmp_tetr);
    brick_to_move_field(game_info_ex);
  }
}

void move_brick_right(ExtendedGameInfo_t *game_info_ex) {
  if (!check_collision_right(game_info_ex)) {
    game_info_ex->tetromino.y++;
    brick_to_move_field(game_info_ex);
  }
}

void move_brick_left(ExtendedGameInfo_t *game_info_ex) {
  if (!check_collision_left(game_info_ex)) {
    game_info_ex->tetromino.y--;
    brick_to_move_field(game_info_ex);
  }
}

bool check_move_to_shift_func(ExtendedGameInfo_t *game_info_ex) {
  bool res = false;
  if (!game_info_ex->timer_activated) {
    game_info_ex->timer = current_time_millis();
    game_info_ex->timer_activated = true;
  }
  long long unsigned int lvl_speed = 1000 / game_info_ex->game_info.level;
  if (time_diff_func(game_info_ex->timer) >= lvl_speed &&
      game_info_ex->state != EXIT_STATE && game_info_ex->game_info.pause != 1) {
    game_info_ex->timer_activated = false;
    game_info_ex->timer = 0;
    res = true;
  }
  return res;
}

bool check_shifting_to_attaching(ExtendedGameInfo_t *game_info_ex) {
  bool res = false;
  if (check_collision_tetromino(game_info_ex->move_field,
                                game_info_ex->touched_field) ||
      check_collision_bottom(game_info_ex->move_field)) {
    res = true;
  }
  return res;
}

void move_brick(ExtendedGameInfo_t *game_info_ex) {
  game_info_ex->tetromino.x++;
  brick_to_move_field(game_info_ex);
}

void move_from_move_to_touch(ExtendedGameInfo_t *game_info_ex) {
  for (int i = 0; i < ROWS_MAP; i++)
    for (int j = 0; j < COLS_MAP; j++)
      if (game_info_ex->move_field[i][j] == 1) {
        game_info_ex->touched_field[i][j] = 1;
        game_info_ex->move_field[i][j] = 0;
      }
}

void check_y_after_action(ExtendedGameInfo_t *game_info_ex) {
  int y = game_info_ex->tetromino.y;
  if (y == -1) {  // y - координата левого верхнего угла
    for (int i = 0; i < 4; i++)
      if (game_info_ex->tetromino.brick[i][0] == 1) game_info_ex->tetromino.y++;
  }
  if (y == 7) {
    for (int i = 0; i < 4; i++)
      if (game_info_ex->tetromino.brick[i][3] == 1) game_info_ex->tetromino.y--;
  }
  if (y == 8) {
    for (int i = 0; i < 4; i++)
      if (game_info_ex->tetromino.brick[i][2] == 1) game_info_ex->tetromino.y--;
  }
}

bool check_x_after_action(ExtendedGameInfo_t *game_info_ex) {
  bool res = false;
  int x = game_info_ex->tetromino.x;
  if (x == 17) {
    for (int j = 0; j < 4; j++)
      if (game_info_ex->tetromino.brick[3][j] == 1) res = true;
  }
  if (x == 18) {
    for (int j = 0; j < 4; j++)
      if (game_info_ex->tetromino.brick[2][j] == 1) res = true;
  }
  if (x == 19) {
    for (int j = 0; j < 4; j++)
      if (game_info_ex->tetromino.brick[1][j] == 1) res = true;
  }
  return res;
}

bool check_collision_bottom(int move_field[][COLS_MAP]) {
  for (int j = 0; j < COLS_MAP; j++)
    if (move_field[19][j] == 1) return true;
  return false;
}

bool check_collision_left(ExtendedGameInfo_t *game_info_ex) {
  bool res = false;
  if (game_info_ex->tetromino.y == 0) {
    for (int i = 0; i < 4; i++)
      if (game_info_ex->tetromino.brick[i][0] == 1) res = true;
  }
  if (game_info_ex->tetromino.y == -1) {
    for (int i = 0; i < 4; i++)
      if (game_info_ex->tetromino.brick[i][1] == 1) res = true;
  }
  for (int i = 0; i < ROWS_MAP; i++)
    for (int j = 1; j < COLS_MAP;
         j++)  // -1 так как проверяем j+1 и превышение будет
      if (game_info_ex->move_field[i][j] == 1 &&
          game_info_ex->touched_field[i][j - 1] == 1)
        res = true;
  return res;
}

bool check_collision_right(ExtendedGameInfo_t *game_info_ex) {
  bool res = false;
  if (game_info_ex->tetromino.y == 6) {
    for (int i = 0; i < 4; i++)
      if (game_info_ex->tetromino.brick[i][3] == 1) res = true;
  }
  if (game_info_ex->tetromino.y == 7) {
    for (int i = 0; i < 4; i++)
      if (game_info_ex->tetromino.brick[i][2] == 1) res = true;
  }
  if (game_info_ex->tetromino.y == 8) {
    for (int i = 0; i < 4; i++)
      if (game_info_ex->tetromino.brick[i][1] == 1) res = true;
  }
  for (int i = 0; i < ROWS_MAP; i++)
    for (int j = 0; j < COLS_MAP - 1;
         j++)  // -1 так как проверяем j+1 и превышение будет
      if (game_info_ex->move_field[i][j] == 1 &&
          game_info_ex->touched_field[i][j + 1] == 1)
        res = true;
  return res;
}

bool check_collision_tetromino(int move_field[][COLS_MAP],
                               int touched_field[][COLS_MAP]) {
  bool res = false;
  for (int i = 0; i < ROWS_MAP; i++)
    for (int j = 0; j < COLS_MAP; j++)
      if (move_field[i][j] == 1 && touched_field[i + 1][j] == 1) res = true;
  return res;
}

bool check_tetr_collision_after_action(ExtendedGameInfo_t *game_info_ex) {
  bool res = false;
  for (int i = 0; i < ROWS_MAP; i++)
    for (int j = 0; j < COLS_MAP; j++) {
      if (game_info_ex->move_field[i][j] == 1 &&
          game_info_ex->touched_field[i][j] == 1)
        res = true;
    }
  return res;
}

unsigned long long time_diff_func(unsigned long long timer) {
  return current_time_millis() - timer;
}

unsigned long long current_time_millis() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (unsigned long long)(tv.tv_sec) * 1000 +
         (unsigned long long)(tv.tv_usec) / 1000;
}