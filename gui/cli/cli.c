#include "cli.h"

static void print_border(void);
static void print_stats(GameInfo_t game_info);
static void print_field(GameInfo_t game_info);
static void print_game_over(void);
static void print_pause(void);
static void print_start_screen(void);
static void print_control_keys(void);

void frontend_general_func(GameInfo_t game_info) {
  clear();
  if (game_info.field == NULL)
    print_start_screen();
  else {
    print_stats(game_info);
    print_field(game_info);
  }
  if (game_info.pause == 1) {
    print_pause();
  }
  if (game_info.pause == 2) {
    print_game_over();
  }
  print_control_keys();
  print_border();
  refresh();
}

void enable_ncurses(void) {
  initscr();
  curs_set(0);
  cbreak();
  halfdelay(1);
  keypad(stdscr, TRUE);
}

void disable_ncurses(void) { endwin(); }

static void print_border(void) {
  const char border = '|';
  int row = 22, col = 22;
  for (int i = 0; i < row; i++)
    for (int j = 0; j < col; j++) {
      if (i == 0) {
        mvaddch(i, j, border);
      }
      if (i == row - 1) {
        mvaddch(i, j, border);
      }
      if (j == 0 && i > 0) {
        mvaddch(i, j, border);
      }
      if (j == col - 1 && i > 0) {
        mvaddch(i, j, border);
      }
    }
}

static void print_stats(GameInfo_t game_info) {
  mvaddstr(0, 24, "The highest Score");
  mvprintw(1, 24, "%d", game_info.highest_score);

  mvaddstr(2, 24, "Current score");
  mvprintw(3, 24, "%d", game_info.score);

  mvaddstr(4, 24, "Level");
  mvprintw(5, 24, "%d", game_info.level);

  mvaddstr(6, 24, "Speed");
  mvprintw(7, 24, "%d", game_info.speed);

  mvaddstr(9, 24, "Next");
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 4; j++)
      if (game_info.next[i][j] == 1) {
        mvaddch(i + 11, j * 2 + 24, '[');
        mvaddch(i + 11, j * 2 + 25, ']');
      }
}

static void print_field(GameInfo_t game_info) {
  for (int i = 0; i < 20; i++)
    for (int j = 0; j < 10; j++)
      if (game_info.field[i][j] == 1) {
        mvaddch(i + 1, j * 2 + 1, '[');
        mvaddch(i + 1, j * 2 + 2, ']');
      }
}

static void print_start_screen(void) { mvaddstr(10, 2, "Press 's' to start"); }

static void print_control_keys(void) {
  mvaddstr(14, 24, "s - start");
  mvaddstr(15, 24, "e - exit");
  mvaddstr(16, 24, "r - action");
  mvaddstr(17, 24, "p - pause, unpause");
  mvaddstr(18, 24, "<-,->  - left and right move");
  mvaddstr(19, 24, "down arrow  - fast move down");
}

static void print_game_over(void) {
  mvaddstr(9, 1, "=====================");
  mvaddstr(10, 7, "GAME OVER");
  mvaddstr(11, 1, "=====================");
  mvaddstr(12, 1, "Press 's' to restart");
  mvaddstr(13, 1, "=====================");
}

static void print_pause(void) {
  mvaddstr(9, 1, "=====================");
  mvaddstr(10, 8, "Pause");
  mvaddstr(11, 1, "=====================");
  mvaddstr(12, 1, "Press 'p' to resume");
  mvaddstr(13, 1, "=====================");
}
