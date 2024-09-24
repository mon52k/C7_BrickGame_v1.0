#include "tetris_logic.h"

void generate_next_func(ExtendedGameInfo_t *game_info_ex) {
  int index = rand() % 7;
  if (index == 0) {
    int i[4][4] = {{0, 0, 0, 0}, {1, 1, 1, 1}, {0}, {0}};
    fill_next_func(&(game_info_ex->game_info), i);
    game_info_ex->tetromino.next_type = 'i';
  }
  if (index == 1) {
    int o[4][4] = {{0, 1, 1, 0}, {0, 1, 1, 0}, {0}, {0}};
    fill_next_func(&(game_info_ex->game_info), o);
    game_info_ex->tetromino.next_type = 'o';
  }
  if (index == 2) {
    int t[4][4] = {{0, 1, 0, 0}, {1, 1, 1, 0}, {0}, {0}};
    fill_next_func(&(game_info_ex->game_info), t);
    game_info_ex->tetromino.next_type = 't';
  }
  if (index == 3) {
    int j[4][4] = {{1, 0, 0, 0}, {1, 1, 1, 0}, {0}, {0}};
    fill_next_func(&(game_info_ex->game_info), j);
    game_info_ex->tetromino.next_type = 'j';
  }
  if (index == 4) {
    int l[4][4] = {{0, 0, 1, 0}, {1, 1, 1, 0}, {0}, {0}};
    fill_next_func(&(game_info_ex->game_info), l);
    game_info_ex->tetromino.next_type = 'l';
  }
  if (index == 5) {
    int s[4][4] = {{0, 1, 1, 0}, {1, 1, 0, 0}, {0}, {0}};
    fill_next_func(&(game_info_ex->game_info), s);
    game_info_ex->tetromino.next_type = 's';
  }
  if (index == 6) {
    int z[4][4] = {{1, 1, 0, 0}, {0, 1, 1, 0}, {0}, {0}};
    fill_next_func(&(game_info_ex->game_info), z);
    game_info_ex->tetromino.next_type = 'z';
  }
}

void next_to_tetromino(ExtendedGameInfo_t *game_info_ex) {
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      game_info_ex->tetromino.brick[i][j] = game_info_ex->game_info.next[i][j];
  game_info_ex->tetromino.x = 0;  // высота по€лвени€ брика
  game_info_ex->tetromino.y = 4;  // ширина по€влени€ брика
  game_info_ex->tetromino.current_type = game_info_ex->tetromino.next_type;
  game_info_ex->tetromino.next_type = 0;
}

void fill_next_func(GameInfo_t *game_inf, int next[][4]) {
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) game_inf->next[i][j] = next[i][j];
}

void turn_stick_func(Tetromino *tetromino) {
  int turned_tetromino[4][4] = {0};
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) turned_tetromino[j][i] = tetromino->brick[i][j];
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) tetromino->brick[i][j] = turned_tetromino[i][j];
}

void turn_other_func(Tetromino *tetromino) {
  int turned_tetromino[3][3] = {0};
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++) {
      int temp_j = j - 1;
      int temp_i = i - 1;
      int needed_i = 0;
      int needed_j = 0;
      needed_i = temp_j;
      needed_j = -temp_i;
      turned_tetromino[needed_i + 1][needed_j + 1] = tetromino->brick[i][j];
    }
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++) tetromino->brick[i][j] = turned_tetromino[i][j];
}

void copy_tetr(Tetromino *dst, Tetromino *src) {
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++) dst->brick[i][j] = src->brick[i][j];
  dst->x = src->x;
  dst->y = src->y;
  dst->current_type = src->current_type;
  dst->next_type = src->next_type;
}
