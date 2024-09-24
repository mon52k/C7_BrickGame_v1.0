#ifndef C_TETRIS_LOGIC_H_
#define C_TETRIS_LOGIC_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#include "tetris_lib.h"

#define ROWS_MAP 20
#define COLS_MAP 10
#define NEXT_SIZE 4

typedef enum {
  START = 0,
  SPAWN,
  MOVING,
  SHIFTING,
  ATTACHING,
  GAMEOVER,
  PAUSE,
  EXIT_STATE
} State;

typedef struct {
  int brick[4][4];
  int x;
  int y;
  char current_type;
  char next_type;
} Tetromino;

typedef struct {
  GameInfo_t game_info;
  Tetromino tetromino;
  UserAction_t input;
  int move_field[20][10];
  int touched_field[20][10];
  bool new_input;
  State state;
  unsigned long long timer;
  bool timer_activated;
  bool mem_alloc;
} ExtendedGameInfo_t;

void prepare_game_field(ExtendedGameInfo_t *game_info_ex);
void restart_func(ExtendedGameInfo_t *game_info_ex);
void init_func(ExtendedGameInfo_t *game_info_ex);
void dealloc_field(int ***field, int rows);
void fill_zero_func(int **field, int rows, int cols);
void alloc_field_func(int ***field, int rows, int cols);
void reset_static_field(int move_field[][COLS_MAP]);
void delete_filled_line(int touched_field[][COLS_MAP], int line);
int check_filled_line(int touched_field[][COLS_MAP]);

void generate_next_func(ExtendedGameInfo_t *game_info_ex);
void next_to_tetromino(ExtendedGameInfo_t *game_info_ex);
void fill_next_func(GameInfo_t *game_inf, int next[][4]);
void copy_tetr(Tetromino *dst, Tetromino *src);
void turn_stick_func(Tetromino *tetromino);
void turn_other_func(Tetromino *tetromino);

bool check_game_over(ExtendedGameInfo_t *game_info_ex);
void count_game_score(ExtendedGameInfo_t *game_info_ex);
void set_lvl_func(ExtendedGameInfo_t *game_info_ex);
void save_max_score(ExtendedGameInfo_t *game_info_ex);
void load_max_score(ExtendedGameInfo_t *game_info_ex);

void brick_to_move_field(ExtendedGameInfo_t *game_info_ex);
void action_func(ExtendedGameInfo_t *game_info_ex);
void move_brick_right(ExtendedGameInfo_t *game_info_ex);
void move_brick_left(ExtendedGameInfo_t *game_info_ex);
bool check_move_to_shift_func(ExtendedGameInfo_t *game_info_ex);
bool check_shifting_to_attaching(ExtendedGameInfo_t *game_info_ex);
void move_brick(ExtendedGameInfo_t *game_info_ex);
void move_from_move_to_touch(ExtendedGameInfo_t *game_info_ex);
void check_y_after_action(ExtendedGameInfo_t *game_info_ex);
bool check_x_after_action(ExtendedGameInfo_t *game_info_ex);
bool check_collision_bottom(int move_field[][COLS_MAP]);
bool check_tetr_collision_after_action(ExtendedGameInfo_t *game_info_ex);
bool check_collision_left(ExtendedGameInfo_t *game_info_ex);
bool check_collision_right(ExtendedGameInfo_t *game_info_ex);
bool check_collision_tetromino(int move_field[][COLS_MAP],
                               int touched_field[][COLS_MAP]);

unsigned long long current_time_millis();
unsigned long long time_diff_func(unsigned long long timer);

#endif
