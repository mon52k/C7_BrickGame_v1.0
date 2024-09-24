#include "tetris_logic.h"

bool check_game_over(ExtendedGameInfo_t *game_info_ex) {
  bool res = false;
  for (int j = 0; j < COLS_MAP; j++)
    if (game_info_ex->touched_field[0][j] == 1) res = true;
  return res;
}

void count_game_score(ExtendedGameInfo_t *game_info_ex) {
  int filled_lines = 0;
  if ((filled_lines = check_filled_line(game_info_ex->touched_field))) {
    if (filled_lines == 1) game_info_ex->game_info.score += 100;
    if (filled_lines == 2) game_info_ex->game_info.score += 300;
    if (filled_lines == 3) game_info_ex->game_info.score += 700;
    if (filled_lines >= 4) game_info_ex->game_info.score += 1500;
  }
  if (game_info_ex->game_info.score > game_info_ex->game_info.highest_score) {
    game_info_ex->game_info.highest_score = game_info_ex->game_info.score;
    save_max_score(game_info_ex);
  }
  set_lvl_func(game_info_ex);
}

void save_max_score(ExtendedGameInfo_t *game_info_ex) {
  FILE *file = NULL;
  file = fopen("highest_score.txt", "w");
  if (file) {
    fprintf(file, "%d", game_info_ex->game_info.highest_score);
    fclose(file);
  }
}

void load_max_score(ExtendedGameInfo_t *game_info_ex) {
  FILE *file = NULL;
  int highest_score = 0;
  file = fopen("highest_score.txt", "r");
  if (file) {
    fscanf(file, "%d", &highest_score);
    game_info_ex->game_info.highest_score = highest_score;
    fclose(file);
  }
}

void set_lvl_func(ExtendedGameInfo_t *game_info_ex) {
  int lvl = game_info_ex->game_info.level;
  int score = game_info_ex->game_info.score;
  if (lvl < 11 && (score > (lvl * 600))) game_info_ex->game_info.level++;
}