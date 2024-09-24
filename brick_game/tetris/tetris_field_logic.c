#include "tetris_logic.h"

void prepare_game_field(ExtendedGameInfo_t *game_info_ex) {
  if (game_info_ex->game_info.field != NULL) {
    for (int i = 0; i < ROWS_MAP; i++)
      for (int j = 0; j < COLS_MAP; j++)
        if (game_info_ex->move_field[i][j] == 1 ||
            game_info_ex->touched_field[i][j] == 1)
          game_info_ex->game_info.field[i][j] = 1;
        else
          game_info_ex->game_info.field[i][j] = 0;
  }
}

void restart_func(ExtendedGameInfo_t *game_info_ex) {
  reset_static_field(game_info_ex->move_field);
  reset_static_field(game_info_ex->touched_field);
  game_info_ex->game_info.score = 0;
  game_info_ex->game_info.pause = 0;
  game_info_ex->game_info.level = 1;
}

void init_func(ExtendedGameInfo_t *game_info_ex) {
  if (!game_info_ex->mem_alloc) {
    alloc_field_func(&(game_info_ex->game_info.field), ROWS_MAP, COLS_MAP);
    alloc_field_func(&(game_info_ex->game_info.next), NEXT_SIZE, NEXT_SIZE);
    game_info_ex->mem_alloc = true;
  }
  game_info_ex->game_info.level = 1;
  load_max_score(game_info_ex);
}

void dealloc_field(int ***field, int rows) {
  if (*field != NULL) {
    for (int row = 0; row < rows; row++) {
      if ((*field)[row] != NULL) free((*field)[row]);
    }
    free(*field);
  }
  *field = NULL;
}

void fill_zero_func(int **field, int rows, int cols) {
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) field[i][j] = 0;
}

void alloc_field_func(int ***field, int rows, int cols) {
  *field = (int **)malloc(rows * sizeof(int *));
  if (*field != NULL) {
    for (int row = 0; row < rows; row++)
      (*field)[row] = (int *)malloc(cols * sizeof(int));
    fill_zero_func(*field, rows, cols);
  }
}

void reset_static_field(int static_field[][COLS_MAP]) {
  for (int i = 0; i < ROWS_MAP; i++)
    for (int j = 0; j < COLS_MAP; j++) static_field[i][j] = 0;
}

void delete_filled_line(int touched_field[][COLS_MAP], int line) {
  for (int j = 0; j < COLS_MAP; j++) touched_field[line][j] = 0;

  for (int i = line; i > 0; i--)
    for (int j = 0; j < COLS_MAP; j++)
      touched_field[i][j] = touched_field[i - 1][j];
}

int check_filled_line(int touched_field[][COLS_MAP]) {
  int filled_lines = 0;
  int summ = 0;
  for (int i = 19; i > 0; i--) {
    for (int j = 0; j < COLS_MAP; j++) {
      summ += touched_field[i][j];
      if (summ == 10) {
        delete_filled_line(touched_field, i);
        filled_lines += 1;
        i++;  // i прибавляем, т.к. линии опустились, иначе пропустим
      }
    }
    summ = 0;
  }
  return filled_lines;
}
